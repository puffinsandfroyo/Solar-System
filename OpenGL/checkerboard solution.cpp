
#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include "glut.h"

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);    
	glMatrixMode(GL_PROJECTION);// set up appropriate matrices- to be explained 
	glLoadIdentity();// to be explained
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);// to be explained
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void drawCheckerboard( GLint xLowerLeft, GLint yLowerLeft, 
					   GLint boardSize, int numSquaresOnSide, 
					   GLubyte color1_r, GLubyte color1_g, GLubyte color1_b,
					   GLubyte color2_r, GLubyte color2_g, GLubyte color2_b )
{
    // draw back box
	glColor3ub(color1_r, color1_g, color1_b);
	glRecti( xLowerLeft, yLowerLeft, xLowerLeft + boardSize, yLowerLeft + boardSize );

	// draw front boxes
	glColor3ub(color2_r, color2_g, color2_b);
	float boxSize = float(boardSize)/numSquaresOnSide;
	for (int i = 0; i < numSquaresOnSide; i++)
	{
		for (int j = 0; j < numSquaresOnSide; j++)
		{
			if ((i + j)%2 == 0)
			  glRecti( xLowerLeft + int(i*boxSize), yLowerLeft+ int(j*boxSize), 
			           xLowerLeft + int((i+1)*boxSize), yLowerLeft+ int((j+1)*boxSize) );
		}
	}

}

 void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen 

	drawCheckerboard( 10, 10, 320, 29, 0, 128, 128, 255, 128, 64 );
	drawCheckerboard( 400, 100, 220, 4, 0, 255, 0, 0, 0, 255 );
	drawCheckerboard( 350, 350, 120, 2, 0, 128, 0, 128, 0, 64 );

	glFlush();		                 // send all output to display 
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(640,480);     // set the window size
	glutInitWindowPosition(100, 150); // set the window position on the screen
	glutCreateWindow("checkerboard"); // open the screen window(with its exciting title)
	glutDisplayFunc(myDisplay);     // register the redraw function
	myInit();                   
	glutMainLoop(); 		     // go into a perpetual loop
}
