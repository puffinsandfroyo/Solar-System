#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include "glut.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

const float X_MAX = 640;
const float Y_MAX = 480;
const int WIN_X_UPPER_LEFT = 300;
const int WIN_Y_UPPER_LEFT = 150;
const int arraySize = 500;
const int density = 15;
int arrayCurrent = 0;
int x[arraySize];
int y[arraySize];
GLfloat z[arraySize];


void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);      // set the rbg color for when the display is cleared
	glMatrixMode(GL_PROJECTION);           // set up appropriate matrices- to be explained later
	glLoadIdentity();                        // to be explained later
	gluOrtho2D(0.0, X_MAX, 0.0, Y_MAX);    // to be explained later
}

void myDisplay(void)
// redraw function
{

	int i = 0;
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen 

	glColor3ub(250, 250, 250);              // set the drawing color
	while (i < arrayCurrent)
	{
	glPointSize(z[i]);		          //set the point size 
	glBegin(GL_POINTS);               // draw some points 
	
		glVertex2i(x[i], y[i]);
		i++;

		glEnd();
	}
	i = 0;
	while (i < arrayCurrent) 
	{
		y[i] = y[i] - 1;
		i++;
		int direction = rand() % 70;
		int move = rand() % 2;
		if (move == 1) {
			if (direction == 1)
			{
				x[i] = x[i] + 1;
			}
			else if (direction >1 && direction <20)
			{
				x[i] = x[i] - 2;
			}
		}
	}
	if (rand() % density == 0) {
		arrayCurrent++;
	}
	glFlush();		                  // send all output to display 

}

void idle()
{
	Sleep(10);
	// add any updating here
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	int i = 0;
	while (i < arraySize)
	{
		int r = rand() % 640;
		int R = rand() % 5;
		x[i] = r;
		z[i] = R;
		y[i] = Y_MAX;
		i++;
	}
	glutInit(&argc, argv);                          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // set the display mode
	glutInitWindowSize(X_MAX, Y_MAX);                // set the window size
	glutInitWindowPosition(WIN_X_UPPER_LEFT,
		WIN_Y_UPPER_LEFT);       // set the window position on the screen
	glutCreateWindow("Snowfall");   // open the screen window(with its exciting title)
	
		glutDisplayFunc(myDisplay);                     // register the redraw function

		myInit();
		glutIdleFunc(idle);
		glutMainLoop(); // go into a perpetual loop
}

