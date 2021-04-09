#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "glut.h"
#include <iostream>

const float X_MAX = 640;
const float Y_MAX = 480;
const int WIN_X_UPPER_RIGHT = 100;
const int WIN_Y_UPPER_LEFT  = 150;

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);      // set the bg color
	glMatrixMode(GL_PROJECTION);// set up appropriate matrices- to be explained 
	glLoadIdentity();// to be explained
	gluOrtho2D( 0.0, X_MAX, 0.0, Y_MAX );// to be explained
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void drawCheckerboard(GLint xLowerLeft, GLint yLowerLeft,
	GLint boardSize, int numSquaresOnSide,
	GLubyte color1_r, GLubyte color1_g, GLubyte color1_b,
	GLubyte color2_r, GLubyte color2_g, GLubyte color2_b)
{
	std::cout << numSquaresOnSide << "\n" << boardSize << "\n";
	float length = float(boardSize) / numSquaresOnSide;
	std::cout << length;
	glColor3ub(100, 100, 100);
	glRecti(100, 100, 130, 130);
	glColor3ub(color1_r, color1_g, color1_b);
	glRecti(xLowerLeft, yLowerLeft, xLowerLeft + boardSize, yLowerLeft + boardSize);
	for (int i = 0; i < numSquaresOnSide; i++) {
		glColor3ub(color2_r, color2_g, color2_b);
		
		if (i % 2 == 0) {
			glRecti(xLowerLeft + length*i, length*i,)

		}
	}

	/*for (int i = 0; i < numSquaresOnSide; i++) {
		// Getting the row
		std::cout << "Hello";
		//glRecti(100, 100, 200, 200);
		glColor3ub(color1_r, color1_g, color1_b);
		if (i % 2 == 0) {
			glColor3b(color2_r, color2_g, color2_b);
		}

		glRecti(xLowerLeft + (i * length), yLowerLeft + (i * length), xLowerLeft + length + (i * length), yLowerLeft + length + (i * length));
		//Completing the column

		for (int k = 1; k < numSquaresOnSide; k++) {
			std::cout << "Goodbye";
			glColor3ub(color1_r, color1_g, color1_b);
			if (k % 2 == 0) {
				glColor3b(color2_r, color2_g, color2_b);
			}
			glRecti(xLowerLeft + (k * length), yLowerLeft + (k * length), xLowerLeft + length + (k * length), yLowerLeft + length + (k * length));
		}
	}
	std::cout << length ;
*/
}

 void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen 
	glColor3ub(250, 250, 250);
	drawCheckerboard(0, 0, 200, 10, 200, 110, 15, 24, 200, 10);
	
	glFlush();		                 // send all output to display 
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(X_MAX,Y_MAX);     // set the window size
	glutInitWindowPosition(WIN_X_UPPER_RIGHT, WIN_Y_UPPER_LEFT); // set the window position on the screen
	glutCreateWindow("checkerboard"); // open the screen window(with its exciting title)
	glutDisplayFunc(myDisplay);     // register the redraw function
	myInit();                   
	glutMainLoop(); 		     // go into a perpetual loop
}
