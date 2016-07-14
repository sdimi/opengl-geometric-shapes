#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Dimitris Spathis <sdimitris@csd.auth.gr>
// Ergasia 2a, One Cube

// AEM = 640

// 640mod3 = 1
// a = 15 , b = 70
// rotational vector = [1,2,4]

///////////////////////////////

//GLOBAL VARIABLES
//define a point type to keep coordinates
typedef GLfloat point[3];

//initial rectangle centering on [0,0]
point vertices[4]={{-1,-1,0},{-1,1,0},{1,1,0},{1,-1,0}};
//rotate variables init
static GLfloat angle = 0.0, x = 1.0, y = 1.0, z = 1.0;
//scale variable init
static GLint scale = 1;

void onecube (void)
{
	//creating a list to assign points as cube vertices
	glNewList(1,GL_COMPILE);
		glBegin(GL_QUADS);
			glVertex3fv(vertices[0]);
			glVertex3fv(vertices[1]);
			glVertex3fv(vertices[2]);
			glVertex3fv(vertices[3]);
		glEnd();
	glEndList();


	// top
	glPushMatrix();
	glColor3f(0.5,1,0.5);
	glTranslatef(0,1,0);
	glRotatef(90,1,0,0);
	glCallList(1);
	glPopMatrix();

    // down
	glPushMatrix();
	glColor3f(1,0,1);
	glTranslatef(0,-1,0);
	glRotatef(90,1,0,0);
	glCallList(1);
	glPopMatrix();

    //right
	glPushMatrix();
	glColor3f(1,1,0.8);
	glTranslatef(1,0,0);
	glRotatef(90,0,1,0);
	glCallList(1);
	glPopMatrix();

    // left
	glPushMatrix();
	glColor3f(0.7,1,1);
	glTranslatef(-1,0,0);
	glRotatef(90,0,1,0);
	glCallList(1);
	glPopMatrix();

    // front
	glPushMatrix();
	glColor3f(1,0.5,0);
	glTranslatef(0,0,1);
	glCallList(1);
	glPopMatrix();

    // back
	glPushMatrix();
	glColor3f(0.5,0,1);
	glTranslatef(0,0,-1);
	glCallList(1);
	glPopMatrix();

}


void draw (void)
{
    //white background
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//clipping plane coordinates
    glOrtho(-100.0, 100.0, -100.0, 100.0, 20.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
	//b=70 translate to z negatives
	glTranslatef(0,0,-70);
	//a=15 cube rectangle
	glScalef(7.5, 7.5, 7.5);
	//// rotational vector = [1,2,4]
	glRotatef(angle, 1.0, 2.0, 4.0);


    // draw first cube
	glPushMatrix();
	glTranslatef(6,0,0);
	glRotatef(angle, 1.0, 2.0, 4.0);
	glScalef(x, y, z);
	onecube();
	glPopMatrix();

    // draw second cube
	glPushMatrix();
	glTranslatef(-6,0,0);
	glRotatef(angle, 1.0, 2.0, 4.0);
	glScalef(x, y, z);
	onecube();
	glPopMatrix();


	glutSwapBuffers();

}



// rotation and scaling adjustments
void idle(void)
{
	angle += 1.5;
	if ( angle > 360.0 )
	{
		angle -= 360.0;
	}

	if (scale==0)
	{
		if(x>=1)
			x -=0.05;
		else
			scale=1;

		if(z>=1)
			z -=0.05;
		else
			scale=1;

		if(y>=1)
			y -=0.05;
		else
			scale=1;
	}

	if (scale==1)
	{
		if(y<2)
			y +=0.05;
		else
			scale=0;

		if(x<2)
			x +=0.05;
		else
			scale=0;

		if(z<2)
			z +=0.05;
		else
			scale=0;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cubes");
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
