
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


// Dimitris Spathis <sdimitris@csd.auth.gr>
// Ergasia 3b, Sun + House

// AEM = 640

//Kanoniko tetraedo eggegrammeno se monadiaia sfaira
typedef float point[4];

point v[]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},
          {-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};



//Ekswteriko ginomeno dyo dianysmatwn poy vriskontai
//sto epipedo toy polygwnou 
void out_product(GLfloat *a, GLfloat *b,GLfloat *c,GLfloat *d)
{
	d[0]=(b[1]-a[1])*(c[2]-a[2])-(b[2]-a[2])*(c[1]-a[1]);
	d[1]=(b[2]-a[2])*(c[0]-a[0])-(b[0]-a[0])*(c[2]-a[2]);
	d[2]=(b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[2]);
}


//Trigwno - Ekswteriko ginomeno
void eksgin_tri(GLfloat *a, GLfloat *b,GLfloat *c,GLfloat *d)
{
	GLfloat temp1[3];
	out_product(a,b,c,temp1);
	int i;
	for (i=0;i<3;i++)
	{
		d[i]=temp1[i];
	}
}



//Parallhlogrammo - Ekswteriko ginomeno
void eksgin_rect(GLfloat *a, GLfloat *b,GLfloat *c,GLfloat *d,GLfloat *e)
{
	GLfloat temp1[3];
	out_product(a,b,c,temp1);
	int i;
	for (i=0;i<3;i++)
	{
		e[i]=temp1[i];
	}
}



//Arxiko trigwno poy ginetai gasket-sphere
void triangle(point a, point b, point c)

{
	glBegin(GL_POLYGON);
		glNormal3fv(a);
		glVertex3fv(a);
		glNormal3fv(b);
		glVertex3fv(b);
		glNormal3fv(c);
		glVertex3fv(c);
    	glEnd();
}





//Arxikopoihsh tetragwnou
void Tetragono()
{
    GLfloat sq1[3]={-5.0,5.0,10.0};
	GLfloat sq2[3]={-5.0,-5.0,10.0};
	GLfloat sq3[3]={5.0,-5.0,10.0};
	GLfloat sq4[3]={5.0,5.0,10.0};
	GLfloat n[3];
    eksgin_rect(sq1,sq2,sq3,sq4,n);
      glBegin(GL_POLYGON);
        glNormal3fv(n);
        glVertex3fv(sq1);
	    glVertex3fv(sq2);
 	    glVertex3fv(sq3);
	    glVertex3fv(sq4);
	  glEnd();
}

//Arxikopoihsh trigwnou
void Trigono()
{
    GLfloat tr1[]={-5.0,0.0,0.0};
	GLfloat tr2[]={5.0,0.0,0.0};
	GLfloat tr3[]={0.0,sqrt(75),0.0};
	GLfloat n[3];
	eksgin_tri(tr1,tr2,tr3,n);
     glBegin(GL_POLYGON);
        glNormal3fv(n);
        glVertex3fv(tr1);
	    glVertex3fv(tr2);
 	    glVertex3fv(tr3);
	  glEnd();
}

//Arxikopoihsh orthogwniou
void Orthogonio()
{
    GLfloat rec1[3]={-5.0,0.0,10.0};
	GLfloat rec2[3]={5.0,0.0,10.0};
	GLfloat rec3[3]={5.0,0.0,-10.0};
	GLfloat rec4[3]={-5.0,0.0,-10.0};
    GLfloat n[3];
	eksgin_rect(rec1,rec2,rec3,rec4,n);

      glBegin(GL_POLYGON);
        glNormal3fv(n);
        glVertex3fv(rec1);
	    glVertex3fv(rec2);
 	    glVertex3fv(rec3);
	    glVertex3fv(rec4);
	  glEnd();
}

//Arxikopoihsh grasidiou
void Grasidi()
{
    GLfloat gras1[]={-80.0,-5,-80.0};
	GLfloat gras2[]={-80.0,-5.0,80.0};
	GLfloat gras3[]={80.0,-5.0,80.0};
	GLfloat gras4[]={80.0,-5.0,-80.0};
    GLfloat n[3];
	eksgin_rect(gras1,gras2,gras3,gras4,n);
     glBegin(GL_POLYGON);
        glNormal3fv(n);
        glVertex3fv(gras1);
	    glVertex3fv(gras2);
 	    glVertex3fv(gras3);
	    glVertex3fv(gras4);
	  glEnd();
}

//Normalization twn shmeiwn ths anadromikhs ypodiaireshs
//Kinhsh wste na paroyn th swsth topothethsh
void normalize(point p)
{
    float d =0.0;
    int i;
    for(i=0; i<3; i++) d+=p[i]*p[i];
    d=sqrt(d);
    if(d>0.0) for(i=0; i<3; i++) p[i]/=d;

}


//Anadromiki ypodiairesi twn trigwnwn
void subdivision(point a, point b, point c,int m)
{

    point v1, v2, v3;
    int j;
    if(m>0)
    {
        for(j=0; j<3; j++) v1[j]=a[j]+b[j];
        normalize(v1);
        for(j=0; j<3; j++) v2[j]=a[j]+c[j];
        normalize(v2);
        for(j=0; j<3; j++) v3[j]=b[j]+c[j];
        normalize(v3);
        subdivision(a, v1, v2, m-1);
        subdivision(c, v2, v3, m-1);
        subdivision(b, v3, v1, m-1);
        subdivision(v1, v3, v2, m-1);
    }
    else(triangle(a,b,c));
}



//Epanalambanoyme th diadikasia gia kathena apo ta 4 trigwna
void sphere(void)
{

    subdivision(v[0], v[1], v[2],4);
    subdivision(v[3], v[2], v[1],4);
    subdivision(v[0], v[3], v[1],4);
    subdivision(v[0], v[2], v[3],4);

}


//Listes me ta parapanw stoixeia
void createDL()
{
    glNewList(1,GL_COMPILE);

        Tetragono();

	glEndList();


    glNewList(2,GL_COMPILE);

        Trigono();

	glEndList();

    glNewList(3,GL_COMPILE);

        Orthogonio();

	glEndList();

    glNewList(4,GL_COMPILE);

        Grasidi();

	glEndList();

	glNewList(5,GL_COMPILE);

       sphere();

    glEndList();
}











//house angle
float angle=0;

//sun angle
float gwnia_hliou=0;
float x=0;
float z=0;


void Idle()
{
	angle+=0.1;
    gwnia_hliou+=0.3;
	if (angle >= 360)
	{
	angle=angle-360;
	}
	if (gwnia_hliou >= 180)
	{
	gwnia_hliou=gwnia_hliou-180;
	}

	//diafora fashs hlioy/parathrhth me xrhsh trigwnometrias
	x=80*sin(2*3.14159*angle/360);
	z=80*cos(2*3.14159*angle/360);

	glutPostRedisplay();

}

void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		angle-=20;
		if (angle <= 0){
			angle=360+angle;
		}
	x=80.0*cos(2*3.14159*angle/360);
	z=80.0*sin(2*3.14159*angle/360);

		glutPostRedisplay();
	}
	else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
		angle+=20;
		if (angle >= 360){
			angle=angle-360;
		}

	x=80.0*cos(2*3.14159*angle/360);
	z=80.0*sin(2*3.14159*angle/360);

		glutPostRedisplay();
	}
}

void keys(unsigned char key, int x, int y)
{
//press 'a' or 'd'
   if(key == 'a')
   {
   		angle+=20;
		if (angle >= 360){
			angle=angle-360;
		}

		x=80.0*cos(2*3.14159*angle/360);
		z=80.0*sin(2*3.14159*angle/360);

		glutPostRedisplay();
}

	else if (key == 'd')
   {

   		angle-=20;
		if (angle >= 360){
			angle=angle-360;
		}

		x=80.0*cos(2*3.14159*angle/360);
		z=80.0*sin(2*3.14159*angle/360);

		glutPostRedisplay();

	}

}

//Arxikopoihsh kosmou-skhnhs
void initWorld()
{
	glClearColor (0.0, 0.0, 0.0, 1.0); 

	//parametroi fwtos
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };


	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glEnable(GL_SMOOTH); 
    glEnable(GL_LIGHTING); 
    glEnable(GL_LIGHT0);  
    glEnable(GL_DEPTH_TEST);
    createDL();
    glMatrixMode(GL_PROJECTION);
   	glLoadIdentity();
   	glOrtho(-60.0,60.0,-60.0,60.0, -20.0, 200.0); 
	glMatrixMode(GL_MODELVIEW);


}


//Dhmiourgia skhnis
void SceneCreation()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    GLfloat light_pos[]={ 0.0,0.0,0.0,1.0};
    GLfloat house_specular[]={0.0,0.0,0.0,1.0};
	GLfloat house_dif_amb[]={0.54, 0.27, 0.07,1.0};
	GLfloat roof_specular[]={0.80,0.80,0.80,1.0};
	GLfloat roof_dif_amb[]={0.5,0.5,0.5,1.0};
	GLfloat grass_dif[]={0.5,1.0,0.0,1.0};
	GLfloat no_mat[]={0.0,0.0,0.0,1.0};
	GLfloat high_shine[]={100.0}; //syntelesths gyaladas
	GLfloat no_shine[]={0.0};
	GLfloat emission[]={1.0,1.0,0.0,1.0};

	//Epifaneies spitiou
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,house_dif_amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,house_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glPushMatrix(); 
	glCallList(1);
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef(0,0,-20);
	glCallList(1);
	glPopMatrix();


	glPushMatrix(); 
	glRotatef(90,0,0,1);
	glTranslatef(0,-5,0);
	glRotatef(180,1,0,0);
	glCallList(3);
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef(-5,0,0);
	glRotatef(90,0,0,1);
	glCallList(3);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(0,-5,0);
	glCallList(3);
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef(0,5,0);
	glCallList(3);
	glPopMatrix();

	//Orofh spitiou
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,roof_dif_amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,roof_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,high_shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glPushMatrix();
	//aristerh orofh
	glTranslatef(-5,5,0); 
	glRotatef(60,0,0,1);
	glTranslatef(5,0,0);
	glCallList(3);
	glPopMatrix();

	glPushMatrix();
	//deksia orofh
	glTranslatef(5,5,0);	
	glRotatef(-60,0,0,1);
	glTranslatef(-5,0,0);
	glCallList(3);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,5,10); 
    glCallList(2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,5,-10);
    glCallList(2);
	glPopMatrix();

	//Fwtismos grasidiou
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,grass_dif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shine);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	glPushMatrix(); 
	glCallList(4);
	glPopMatrix();

	//Fwtismos hliou
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,no_mat);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,no_shine);

	glPushMatrix();
	glRotatef(-gwnia_hliou,0,0,1); 
	glTranslatef(-50,0,0);
	//kateythynsh parallhlhs kinhshs se omogeneis syntetagmenes
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
	glScalef(2,2,2);
	glCallList(5);
	glPopMatrix();

	glutSwapBuffers();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
	gluLookAt(x,80,z,0,0,0,0,1,0);
	glEnable(GL_NORMALIZE);
	SceneCreation();


}

int main(int argc, char** argv)
{
   	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize (600, 600);
   	glutInitWindowPosition (0, 0);
	glutCreateWindow("Sun + House");

   	initWorld();

	glutMouseFunc(mouse);
	glutKeyboardFunc(keys);
	glutDisplayFunc(display);
	glutIdleFunc (Idle);
	glEnable(GL_DEPTH_TEST);

   	glutMainLoop();

}

