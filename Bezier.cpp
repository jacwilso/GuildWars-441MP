#include "Bezier.h"

Bezier::Bezier(){};

// push the points onto the control point vector
Bezier::Bezier(Point p0, Point p1, Point p2, Point p3){
  p.push_back(p0);
  p.push_back(p1);
  p.push_back(p2);
  p.push_back(p3);
}

// evaluates points along the curve with the specified bezier curve, with the percentage along the curve
Point Bezier::evaluateCurve(int bez,float t) {
  return pow(1-t,3)*p[bez]+3*pow(1-t,2)*t*p[bez+1]+3*(1-t)*pow(t,2)*p[bez+2]+pow(t,3)*p[bez+3];
}
// Calculates the slope of at that specific point
Point Bezier::derivative(int bez,float t) {
  return( -3*pow(1-t,2)*p[bez]+
          -6*(1-t)*t*p[bez+1]+
            3*pow(1-t,2)*p[bez+1]+
          6*(1-t)*t*p[bez+2]
            -3*pow(t,2)*p[bez+2]+
          3*pow(t,2)*p[bez+3]);
}
// Takes derivative given a parameter
Point Bezier::paramDerivative(int pos) {
  int bez=4*(pos/RESOLUTION);
  float t=(float)(pos%RESOLUTION)/RESOLUTION;
  return derivative(bez,t);
}
/*
 * Calculates the arc Derivative
 */
Point Bezier::arcDerivative(int arcStep){
  float arc=(float)(arcStep)*(float)(arcSize())/resSize();
  if(arc!=0 || arc!=p.size()/4)
    popTab(arc);
  int bez=floor(arcParam[arc]);
  return derivative(4*bez,arcParam[arc]-bez);
}

// render the curve -- same code as lab03
void Bezier::renderCurve() {
  glDisable(GL_LIGHTING);
  glColor3f(0,0,1.0f);
  glLineWidth(3.0f);
  glBegin(GL_LINE_STRIP);
  for(unsigned int j=0; j<p.size()/4; j++){ // goes through each bezier curve if multiple joined
    for(int i=0; i<=RESOLUTION; i++){ 
      Point temp=evaluateCurve(4*j,(float)(i)/RESOLUTION);
      glVertex3f(temp.getX(),temp.getY(),temp.getZ());
    }
  }
  glEnd();
  glEnable(GL_LIGHTING);
}

// render the control points -- same code as lab03
void Bezier::renderPoints(){
  glColor3f(0,1,0);
  for(unsigned int i=0; i<p.size(); i++){
    glPushMatrix();
      glTranslatef(p[i].getX(),p[i].getY(),p[i].getZ());
      glutSolidSphere(.3,32,32);
    glPopMatrix();
  }
}

// render the control cage -- same code as lab03
void Bezier::renderCage(){
  glColor3f(1.0f,1.0f,0);
  glLineWidth(3.0f);
  glDisable(GL_LIGHTING);
  glBegin(GL_LINE_STRIP);
  for(unsigned int i=0; i<p.size(); i++)
      glVertex3f(p[i].getX(),p[i].getY(),p[i].getZ());
    glEnd();
    glEnable(GL_LIGHTING);
}

// connect another bezier curve onto the current -- add the control points to the vector
void Bezier::bezierConnect(Bezier bez){
  for(unsigned int i=0; i<bez.p.size(); i++)
    this->p.push_back(bez.p[i]);
  populateTable();
}

// track the point on the curve the pos is currently at
Point Bezier::parametricCurve(int pos){
  return evaluateCurve(4*(pos/RESOLUTION),(float)(pos%RESOLUTION)/RESOLUTION);
}
/*
 * Populates a table to be used for parameter coordiantes
 */
void Bezier::populateTable(){
  float dist=0;
  arcParam.clear(); paramArc.clear();
  arcParam[0]=0;
  paramArc[0]=0;
  for(unsigned int i=0; i<p.size(); i+=4)
    for(unsigned int j=0; j<RESOLUTION; j++){
      Point tmp1=evaluateCurve(i,(float)(j)/RESOLUTION);
      Point tmp2=evaluateCurve(i,(float)(j+1)/RESOLUTION);
      //cout<<i<<" "<<(float)(j)/RESOLUTION<<" "<<(float)(j+1)/RESOLUTION<<endl;
      dist+=tmp1.distance(tmp2);
      float t=(float)(j+1)/RESOLUTION+i/4;
      //cout<<"dist "<<dist<<" t "<<t<<endl;
      paramArc[t]=dist;
      arcParam[dist]=t;
    }
}

/*
 * Populate the table
 */
void Bezier::popTab(float arc){
  float left=0,right=paramArc[p.size()/4], leftT=0, rightT=p.size()/4;
  map<float,float>::iterator it=arcParam.begin();
  float tmp;

  it=arcParam.find(arc);
  if(it!=arcParam.end()) return;
  for(it=arcParam.begin(); it!=arcParam.end(); ++it){
    tmp=it->first;
    if(left<tmp && tmp<arc){
      left=tmp;
      leftT=arcParam[left];
    }
    else if(right<tmp && tmp>arc){
      right=tmp;
      rightT=arcParam[right];
    }
  }
  tmp=(arc-left)/(right-left)*(rightT-leftT)+leftT;
  //cout<<"ARC "<<arc<<" T "<<tmp<<endl;
  arcParam[arc]=tmp;
  paramArc[tmp]=arc;
}
/*
 * Evaluates the curve for the arc length
 */
Point Bezier::arcLengthCurve(int arcStep){
  float arc=(float)(arcStep)*(float)(arcSize())/resSize();
  //cout<<"ARC "<<arc<<" SIZE "<<arcSize()<<endl;
  if(arc!=0 || arc!=p.size()/4)
    popTab(arc);
  int bez=floor(arcParam[arc]);
  //cout<<"BEZ "<<bez<<" T "<<arcParam[arc]<<endl;
  return evaluateCurve(4*bez,arcParam[arc]-bez);
}
/*
 * Operator Overloading equal check
 */
void Bezier::operator=(Bezier bez){
  p.clear();
  for(unsigned int i=0; i<bez.p.size(); i++)
    p.push_back(bez.p[i]);
  populateTable();
}
