#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Dimitris Spathis <sdimitris@csd.auth.gr>
// Ergasia 3, House Projections

// AEM = 640



void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);
   	glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-80.0,80.0,-80.0,80.0, 20.0, 120.0);
	glMatrixMode(GL_MODELVIEW);
}


void drawhouse()
{
	glPushMatrix();
	glColor3f(0.5, 1, 0);	//front rectangle
	glCallList(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0.5,0);	//back rectangle
	glTranslatef(0,0,-20);
	glCallList(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);     //down par
	glTranslatef(0,-5,0);
	glCallList(2);

	glColor3f(1, 0.6, 0.8); 	//top par
	glTranslatef(0,10,0);
	glCallList(2);
	glPopMatrix();

    glPushMatrix();
	glColor3f(0.5, 1, 1);
	glTranslatef(5,0,0); //right par
	glRotatef(90,0,0,1);
	glCallList(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.5, 1);	//left par
	glTranslatef(-5,0,0);
	glRotatef(90,0,0,1);
	glCallList(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,1,0.5);
	glTranslatef(-5,5,0); //left roof par
	glRotatef(60,0,0,1);
	glTranslatef(5,0,0);
	glCallList(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7,0.3,0.5);
	glTranslatef(5,5,0);	//right roof par
	glRotatef(-60,0,0,1);
	glTranslatef(-5,0,0);
	glCallList(2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0.2,0.5);
	glTranslatef(0,5,10);   //front roof triangle
	glCallList(3);
	glTranslatef(0,0,-20);	//back roof triangle
	glCallList(3);
	glPopMatrix();

}


void right_click_menu(int id)
 {
    //front
	if(id==1)
	{
	      init ();
		  glLoadIdentity();
		  glTranslatef(0,0,-70);
    }

    //down
	if(id==2)
	{

		  init ();
		  glLoadIdentity();
		  glTranslatef(0,0,-60);
    	  glRotatef(90,1,0,0);

    }

    //right
	if(id==3)
	{

		  init ();
		  glLoadIdentity();
		  glTranslatef(0,0,-60);
    	  glRotatef(-90,0,1,0);
    }

    //isometric
	if(id==4)
	{
		  init ();
		  glLoadIdentity();
		  gluLookAt(20,20,25,5,5,10,0,1,0);
    }

    //perspective
	if(id==5)
	{
		  glMatrixMode(GL_PROJECTION);
	      glLoadIdentity();
		  gluPerspective(90.0, 1, 20, 120);
		  glMatrixMode(GL_MODELVIEW);
		  glLoadIdentity();
		  gluLookAt(20.0, 0.0, 40.0, 0,0,0, 0, 1, 0);
	}

	 glutPostRedisplay();
 }

void basicshapes()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//define a rectangle for house front/back
	glNewList(1,GL_COMPILE);
	  glBegin(GL_POLYGON);
        glVertex3f(-5.0,5.0,10.0);
	    glVertex3f(-5.0,-5.0,10.0);
 	    glVertex3f(5.0,-5.0,10.0);
	    glVertex3f(5.0,5.0,10.0);
	  glEnd();
	glEndList();

	// define a parallelogram for rest of house
	glNewList(2,GL_COMPILE);
	  glBegin(GL_POLYGON);
        glVertex3f(-5.0,0.0,10.0);
	    glVertex3f(5.0,0.0,10.0);
 	    glVertex3f(5.0,0.0,-10.0);
	    glVertex3f(-5.0,0.0,-10.0);
	  glEnd();
	glEndList();

	// define a triangle for roof front/back
	glNewList(3,GL_COMPILE);
	  glBegin(GL_POLYGON);
        glVertex3f(-5.0,0.0,0.0);
	    glVertex3f(5.0,0.0,0.0);
	    //pythagorean theorem
 	    glVertex3f(0.0,sqrt(75),0.0);
	  glEnd();
	glEndList();
	drawhouse();

	glutSwapBuffers();
}


int main(int argc, char** argv)
{
   	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (900, 800);
   	glutInitWindowPosition (0,0);
	glutCreateWindow("House");
   	init ();
	glLoadIdentity();
	glTranslatef(0,0,-60);
	glutDisplayFunc(basicshapes);
	glEnable(GL_DEPTH_TEST);
	glutCreateMenu(right_click_menu);
    glutAddMenuEntry("Front",1);
    glutAddMenuEntry("Down",2);
    glutAddMenuEntry("Right",3);
    glutAddMenuEntry("Isometric",4);
	glutAddMenuEntry("Perspective",5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
   	glutMainLoop();

}
