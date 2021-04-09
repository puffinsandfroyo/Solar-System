#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "glut.h"
#include<iostream>
#include <time.h>
#include <cstdlib>  // for rand()

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);      // set the bg color
	glMatrixMode(GL_PROJECTION);           // set up appropriate matrices- to be explained 
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void idle()
{
	Sleep(2000);
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void drawDiamond( GLint xCenter, GLint yCenter, GLint size )
{
	glColor3ub(rand()%255, rand()%255, rand()%255);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xCenter,yCenter + size);
	glVertex2i(xCenter+size,yCenter);
	glVertex2i(xCenter,yCenter-size);
	glVertex2i(xCenter - size, yCenter);
	glEnd();
	glFlush();

}

 void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen 
	for (int i = 0; i < 50; i++) {
		drawDiamond(rand()%640,rand()%480,1+rand()%100);
	}
	glFlush();	// send all output to display
	idle();
 }
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	srand((unsigned int)time(0));
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(640,480);     // set the window size
	glutInitWindowPosition(100, 150); // set the window position on the screen
	glutCreateWindow("Diamonds"); // open the screen window(with its exciting title)
	glutDisplayFunc(myDisplay);     // register the redraw function
	glutIdleFunc(idle);
	myInit();                   
	glutMainLoop(); 		     // go into a perpetual loop
}
 