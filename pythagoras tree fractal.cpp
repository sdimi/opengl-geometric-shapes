
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

// Dimitris Spathis <sdimitris@csd.auth.gr>
// Ergasia 1b, Pythagoras Tree

void drawtree(int n)
{
    if(n>0)
    {
    //////////////////////////
    //stack of matrices
     glPushMatrix();

     glTranslatef(-0.5,1.0,0);
     glRotatef(45, 0.0, 0.0, 1.0);

     // 1/sqrt(2)=0.707
     glScalef(0.707,0.707,0.707);

     //recursion
     drawtree(n-1);

     glPopMatrix();
    ////////////////////////////

     glPushMatrix();
     glTranslatef(0.5,1.0,0);
     glRotatef(-45, 0.0, 0.0, 1.0);
     glScalef(0.707,0.707,0.707);
     drawtree(n-1);
     glPopMatrix();
     //draw a cube
     glutSolidCube(1);
    }
}

void treeInit(int n)
{
    // draw a red tree
   glColor3f(1.0, 0.0, 0.0);
   drawtree(n);
}

void display (void)
{
    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //initialize with 15 iterations
    treeInit(15);
    glFlush();
}

void reshape (int w, int h)
{
    //reshaoe to aspect ratio
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (80, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE);
    glutInitWindowSize (900, 700);
    glutInitWindowPosition (300, 100);
    glutCreateWindow ("Pythagoras Tree");
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glutMainLoop ();
    return 0;
}
