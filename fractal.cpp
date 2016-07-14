#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Dimitris Spathis <sdimitris@csd.auth.gr>
// Ergasia 1, Fractals
// Based on gascet


void draw();
int pick = 0;
int option;
int points;
double x_initial = 0.00;
double y_initial = 0.00;
void drawPoint(float x, float y);


void init(void)
{
    //random number generator for colors
	srand(GetTickCount());
	glEnable(GL_BLEND);
	//setting background
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// get three random colors based on 256-value hex
	glColor3ub(rand() % 255, rand() % 255, rand() % 255);
	//setting up our projection window of 900x600
	gluOrtho2D(0.0,  900.0, 0.0, 600.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

}

void righClickMenu(int pick)
{
	option = pick;
	glutPostRedisplay();
	glColor3ub(rand() % 255, rand() % 255, rand() % 255);
}

void Menu()
{
	glutCreateMenu(righClickMenu);
	glutAddMenuEntry("Draw a 20.000-particle fractal", 1);
	glutAddMenuEntry("Draw a 50.000-particle fractal", 2);
	glutAddMenuEntry("Exit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawFractal(void)
{
	switch (option) {
	case 0:
		points = 10000;
		draw();
		break;
	case 1:
		points = 20000;
		draw();
		break;
	case 2:
		points = 50000;
		draw();
		break;
	case 3:
		exit(0);
	}
}
void draw()
{

	glEnable(GL_BLEND);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

    //defining a data type of "point"
	typedef GLfloat point2[2];

	// an arbitrary pentagon
	point2 vertices[5] = { { 550, 450 }, { 455, 519 }, { 491, 631 }, { 609, 631 }, { 645, 519 } };

	int j, k;
	// choosing an starting point p
	point2 p = { 75.0, 50.0 };
    //clearing the window
	glClear(GL_COLOR_BUFFER_BIT);

	//code based on gascet
	for (k = 0; k<points; k++)
	{
	    //random vertex
		j = rand() % 5;
		p[0] = (p[0] + vertices[j][0]) / 3;
		p[1] = (p[1] + vertices[j][1]) / 3;

		// plot new point
		drawPoint(p[0]-x_initial,p[1]-y_initial);
	}
	glutSwapBuffers();
}

void drawPoint(float x, float y){
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}


void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		glutPostRedisplay();
	}
}

void motion(int x, int y)
{
	if (x <= 450 && y <= 300){ x_initial += 1; y_initial -= 1; }
	if (x <= 450 && y >  300){ x_initial += 1; y_initial += 1; }
	if (x >  450 && y <= 300){ x_initial -= 1; y_initial -= 1; }
	if (x >  450 && y >  300){ x_initial -= 1; y_initial += 1; }
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(900, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Fractal");
	init();
	glutDisplayFunc(drawFractal);
	Menu();
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
    glutMainLoop();
}

