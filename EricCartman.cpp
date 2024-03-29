#include "EricCartman.h"
#include <cmath>
#include <iostream>

using namespace std;


const float PI = 3.14159;
const float RAD = PI/180;

//constructor
EricCartman::EricCartman(){
		swingAngle=0;
		ericHeadBobAngle=0;
		heroPosY = 3.3;		
}

//draw hemisphere
void drawHemiSphere(float radx,float rady,float radz)
{
		float i,j;
		float t1x,t1y,t1z,t2x,t2y,t2z;

		float side = 4;
		glBegin(GL_QUADS);
		{
				for(i=0;i<91;i+=side)
				{
						for(j=0;j<360;j+=side)
						{
								t1x=(sin(j*RAD)*cos(i*RAD) + sin((j+side)*RAD)*cos((i+side)*RAD))/2;
								t1y=(sin(i*RAD) + sin((i+side)*RAD))/2;
								t1z=(cos(j*RAD)*cos(i*RAD) + cos((j+side)*RAD)*cos((i+side)*RAD))/2;

								t2x=(sin((j+side)*RAD)*cos(i*RAD) + sin(j*RAD)*cos((i+side)*RAD))/2;
								t2y=(sin(i*RAD) + sin((i+side)*RAD))/2;
								t2z=(cos((j+side)*RAD)*cos(i*RAD) + cos(j*RAD)*cos((i+side)*RAD))/2;

								glNormal3f((t1x+t2x)/2,(t1y+t2y)/2,(t1z+t2z)/2);
								glVertex3f(radx*sin(j*RAD)*cos(i*RAD),rady*sin(i*RAD),radz*cos(j*RAD)*cos(i*RAD));
								glVertex3f(radx*sin((j+side)*RAD)*cos(i*RAD),rady* sin(i*RAD),radz*cos((j+side)*RAD)*cos(i *RAD));
								glVertex3f(radx*sin((j+side)*RAD)*cos((i+side)*RAD ),rady*sin((i+side)*RAD),radz*cos((j+side)*RAD)*cos((i+side)*RAD));
								glVertex3f(radx*sin(j*RAD)*cos((i+side)*RAD),rady* sin((i+side)*RAD),radz*cos(j*RAD)*cos(( i+side)*RAD));
						}
				}
		}
		glEnd();
}

// Basic Shapes
void EricCartman::drawCircle(){
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0,0);
		for(int i = 0; i < 361; i++){
				float angle = i*PI/180.0;
				glVertex3f(50*cos(angle),50*sin(angle),0);
		}

		glEnd();
		glPopMatrix();
}

// Getters
float EricCartman::getSwingAngle(){
		return swingAngle;
}
float EricCartman::getEricHeadBobAngle(){
		return ericHeadBobAngle;
}
float EricCartman::getRotAxisX(){
		return rotAxisX;
}
float EricCartman::getRotAxisZ(){
		return rotAxisZ;
}

// Setters
void EricCartman::setSwingAngle(float item){
		swingAngle = item;
}
void EricCartman::setEricHeadBobAngle(float item){
		ericHeadBobAngle = item;
}
void EricCartman::setRotAxisX(float item){
	rotAxisX = item;
}
void EricCartman::setRotAxisZ(float item){
	rotAxisZ = item;
}

//draw the hero
void EricCartman::drawHero(){
		glPushMatrix();
		{
				glTranslatef(heroPosX, heroPosY, heroPosZ);
				glRotatef(getHeroPhi(), getRotAxisX(), 0, getRotAxisZ());		

				glRotatef(heroTheta, 0,1,0);
				
				glScalef(0.8,0.8,0.8);
                                void *StrFont = GLUT_STROKE_ROMAN;
		                const char* c;
		                glDisable(GL_LIGHTING);
		                  glPushMatrix();
		                  glColor3f(1,1,1);
		                  glTranslatef(-1,8,3.5);
                                  glRotatef(90,0,1,0);
		                  glScalef(.01,.01,.01);
		                  for(c="kentokomoto"; *c!='\0'; c++)
		                		glutStrokeCharacter(StrFont,*c);
		                glPopMatrix();
		                glEnable(GL_LIGHTING);
				drawBody();
		}
		glPopMatrix();

}

//draw body
void EricCartman::drawBody(){

		// Draw the Fairy



		// Draw the line and buttons
		glColor3f(1,0,0);
		glPushMatrix();
		glScalef(1.5,1,1.5);
		glutSolidSphere(3,50,50);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0,0,0);
		glLineWidth(10);
		glScalef(1.5,1,1.5);
		glBegin(GL_LINE_STRIP);
		for(float i = 45; i > -20; i-= 0.1){
				glVertex3f(3*cos(i*PI/180), 3*sin(i*PI/180),0);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(0,0,0);
		glLineWidth(10);
		glScalef(1.5,1,1.5);
		glBegin(GL_LINE_STRIP);
		for(float i = 35; i > 30; i-= 0.2){
				glVertex3f(3*cos(i*PI/180), 3*sin(i*PI/180),0.5);
		}
		glEnd();
		glPopMatrix();


		glPushMatrix();
		glColor3f(0,0,0);
		glLineWidth(10);
		glScalef(1.5,1,1.5);
		glBegin(GL_LINE_STRIP);
		for(float i = 20; i > 15; i-= 0.2){
				glVertex3f(3*cos(i*PI/180), 3*sin(i*PI/180),0.5);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(0,0,0);
		glLineWidth(10);
		glScalef(1.5,1,1.5);
		glBegin(GL_LINE_STRIP);
		for(float i = 0; i > -5; i-= 0.2){
				glVertex3f(3*cos(i*PI/180), 3*sin(i*PI/180),0.5);
		}
		glEnd();
		glPopMatrix();
		glLineWidth(1);

		// Draw the feet
		glPushMatrix();
		glRotatef(20*sin(getSwingAngle()*RAD),0,0,1);	// Rotate for walking
		glTranslatef(0,-1.5,1.5);
		drawFeet();
		glPopMatrix();

		glPushMatrix();
		glRotatef(-20*sin(getSwingAngle()*RAD),0,0,1); // Rotate for walking
		glTranslatef(0,-1.5,-1.5);
		drawFeet();
		glPopMatrix();

		// Draw Hands
		glPushMatrix();
		glRotatef(-20*sin(getSwingAngle()*RAD), 0, 0, 1);
		glRotatef(-35,1,0,0);
		glTranslatef(0,-0.8,3.5);
		drawHands();
		glPopMatrix();

		glPushMatrix();
		glRotatef(20*sin(getSwingAngle()*RAD), 0, 0, 1);
		glRotatef(35,1,0,0);
		glTranslatef(0,-0.8,-3.5);
		drawHands();
		glPopMatrix();

		// Draw Head
		glPushMatrix();
		glTranslatef(0,0.2*sin(getEricHeadBobAngle()*RAD)+3.3,0);
		drawHead();
		glPopMatrix();
}

//draw feet
void EricCartman::drawFeet(){
		glPushMatrix();
		glColor3f(0.35 , 0.16 , 0.14);
		glRotatef(90,1,0,0);
		GLUquadricObj *leg;
		leg = gluNewQuadric();
		gluQuadricDrawStyle(leg, GLU_FILL);
		gluCylinder(leg, 1.7,1.5,2,100,100);
		gluDeleteQuadric(leg);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0.3,-2,0);
		glScalef(0.6,0.1,0.6);
		glutSolidSphere(3,50,50);
		glPopMatrix();

}

//draw hands
void EricCartman::drawHands(){
		glPushMatrix();
		glColor3f(1,0,0);
		glRotatef(90,1,0,0);
		GLUquadricObj *arm;
		arm = gluNewQuadric();
		gluQuadricDrawStyle(arm, GLU_FILL);
		gluCylinder(arm, 0.8,1,2.5,100,100);
		gluDeleteQuadric(arm);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1,1,0);
		glTranslatef(0,-2.5,0);
		glutSolidSphere(1.2,50,50);
		glPopMatrix();

}

//draw head
void EricCartman::drawHead(){
		glPushMatrix();
		glColor3f(0,0,0);
		glRotatef(90,1,0,0);
		glTranslatef(3,0,1);
		glutSolidTorus(0.1,1,50,50);
		glPopMatrix();

		glPushMatrix();
		glScalef(1.4,1,1.4);
		{
				//Draw face
				glPushMatrix();
				glColor3f(0.99 , 0.85 , 0.69);
				glutSolidSphere(3,50,50);
				glPopMatrix();

				// Draw the beanie
				glPushMatrix();
				glScalef(1.01,1.01,1.01	);
				glColor3f(0.196078 , 0.6 , 0.8);
				glRotatef(20,0,0,1);
				drawHemiSphere(3,3,3);
				glPopMatrix();

				glPushMatrix();
				glColor3f(1,1,0);
				glRotatef(20,0,0,1);
				glTranslatef(0,3,0);
				drawHemiSphere(0.5,0.5,0.5);
				glPopMatrix();

				glPushMatrix();
				glColor3f(1,1,0);
				glRotatef(20,0,0,1);
				glRotatef(90,1,0,0);
				glutSolidTorus(0.1,3,50,50);
				glPopMatrix();
		}
		glPopMatrix();

		glDisable( GL_LIGHTING );
		glPushMatrix();
		{
				// Right Eye
				glPushMatrix();
				glColor3f(1,1,1);
				glRotatef(90,0,1,0);
				glTranslatef(0.6,0.05,4.2);
				glScalef(0.013,0.015,0.013);
				drawCircle();
				glPopMatrix();

				// Right Pupil
				glPushMatrix();
				glColor3f(0,0,0);
				glRotatef(90,0,1,0);
				glTranslatef(0.35,0.05,4.21);
				glScalef(0.002,0.002,0.002);
				drawCircle();
				glPopMatrix();

				// Left Eye
				glPushMatrix();
				glColor3f(1,1,1);
				glRotatef(90,0,1,0);
				glTranslatef(-0.6,0.05,4.2);
				glScalef(0.013,0.015,0.013);
				drawCircle();
				glPopMatrix();

				// Left Pupil
				glPushMatrix();
				glColor3f(0,0,0);
				glRotatef(90,0,1,0);
				glTranslatef(-0.35,0.05,4.21);
				glScalef(0.002,0.002,0.002);
				drawCircle();
				glPopMatrix();
		}
		glPopMatrix();
		glEnable( GL_LIGHTING );
}

//move forward
void EricCartman::moveEricForward(){
		heroPosX += cos(heroTheta*RAD);
		heroPosZ -= sin(heroTheta*RAD);
		setSwingAngle(getSwingAngle() + 20);


		// Set an invisible wall at borders of grid
		if(getHeroPositionX() > 99){
				heroPosX = 99;
		}else if(getHeroPositionX() < -99){
				heroPosX = -99;
		}
		if(getHeroPositionZ() > 99){
				heroPosZ = 99;
		}else if(getHeroPositionZ() < -99){
				heroPosZ = -99;
		}
}

//move backward
void EricCartman::moveEricBackward(){
		heroPosX -= cos(heroTheta*RAD);
		heroPosZ += sin(heroTheta*RAD);
		setSwingAngle(getSwingAngle() - 20);


		// Set an invisible wall at borders of grid
		if(getHeroPositionX() > 99){
				heroPosX = 99;
		}else if(getHeroPositionX() < -99){
				heroPosX = -99;
		}
		if(getHeroPositionZ() > 99){
				heroPosZ = 99;
		}else if(getHeroPositionZ() < -99){
				heroPosZ = -99;
		}
}

//turn left
void EricCartman::turnEricLeft(){
		heroTheta += 5;

}

//turn right
void EricCartman::turnEricRight(){
		heroTheta -= 5;
}

//animation
void EricCartman::animate(){
		setEricHeadBobAngle(getEricHeadBobAngle() + 10);
}
