#include <windows.h>
#include <gl/Gl.h>
#include "glut.h"
#include <stdlib.h>

int	screenWidth = 640, screenHeight = 480;

void drawDiamond( GLint xCenter, GLint yCenter, GLint size )
{
	glBegin( GL_LINE_LOOP );
		glVertex2i( xCenter, yCenter - size);
		glVertex2i( xCenter + size, yCenter);
		glVertex2i( xCenter, yCenter + size);
		glVertex2i( xCenter - size, yCenter);
	glEnd();
}

void myDisplay() 
{
	glClear( GL_COLOR_BUFFER_BIT );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
 	glPointSize(3.0);		      
	glLineWidth(3.0);

	glFlush();
}

void myMouse( int button, int state, int x, int y ) 
{
	if (state == GLUT_DOWN) {
		glColor3ub(rand() % 255, rand() % 255, rand() % 255);
		if (button == GLUT_LEFT_BUTTON) {
			drawDiamond(x, screenHeight - y, rand() % 200);
			glFlush();
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			glClearColor((float)(rand() % 256) / 255.0f, (float)(rand() % 256) / 255.0f, (float)(rand() % 256) / 255.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
		else if (button == GLUT_MIDDLE_BUTTON) {
			glPointSize(rand() % 10);
		}
	}
	else if (state == GLUT_UP) {

	}
}

void myPassiveMotion( int x, int y )  
{
	//y = -1 * y;
	
	glBegin(GL_POINTS);       // draw some points 
	glVertex2i(x,screenHeight-y);
	glEnd();
	glFlush();
}

int main( int argc, char ** argv ) {

	glutInit( &argc, argv );

	// initialize window
	glutInitWindowSize( screenWidth, screenHeight );
	glutInitWindowPosition( 0, 0 );
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	// create window
	glutCreateWindow( "diamond click" );

	// set the projection matrix
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity();
	gluOrtho2D( 0, screenWidth, 0, screenHeight );

	glMatrixMode( GL_MODELVIEW );
	// clear rendering surface
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // background is black
	glViewport(0, 0, screenWidth, screenHeight);


	glutMouseFunc( myMouse ); //Calls myMouse when a mouseinteraction occurs
	glutDisplayFunc( myDisplay ); //
	glutPassiveMotionFunc( myPassiveMotion ); // gets called whenever the mouse gets moved
	glutMainLoop();

	return( 0 );
}
