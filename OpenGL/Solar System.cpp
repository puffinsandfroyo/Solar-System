/*User-Interaction

Add the following user-interactions:  

Left  mouse-based menu
lights
global ambient light:  on (default), off
positional light 1:  on (default), off 
positional light 2:  on, off (default)
directional light:  on, off (default)  -- optional

Right mouse-based menu
display
mode:  wireframe, filled – flat shading (default), filled – smooth shading
On keyboard button ‘+’  rotate through the three levels of detail
viewing: use polar coordinates to allow the viewer to move their viewpoint along a sphere surrounding the building. When zooming in, the LOD should switch automatically.

As before, please add a star ‘*’ after the currently selected mouse-based menu option as feedback to the user.  
*/



//Kali Note:
/* I have a plan to try to turn the sun transparent. That way we can put a light source on the origin and it will illuminate 
the other plannets. If that doesn't work, we might need to add a bunch of light sources around the sun and dull them a little bit?*/

#include <windows.h>
#include <stdlib.h>
#include "glut.h"
#include <iostream>
using namespace std;

float xView = 0, yView = 0.0, zView = 5.0;

static int year = 0, day = 0, viewChoice = 0;

bool autoMotion = false;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glutSolidSphere(1.0, 20, 16); // draw sun 
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslatef(2.0, 0.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);

	glutSolidSphere(0.2, 10, 8); // draw smaller planet 
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xView, yView, zView, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void setViewChoice()
{
	switch (viewChoice)
	{
	case 0: xView = 0.0; yView = 0.0; zView = 5.0; break;
	case 1: xView = 0.0; yView = 5.0; zView = 5.0; break;	
	}
	reshape(500, 500);
	glutPostRedisplay();
}

void idle(){
	if (autoMotion){
		//day = (day + 10) % 360;
		year = (year + 5) % 360;
		Sleep(50);
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		day = (day + 10) % 360;
		break;
	case 'D':
		day = (day - 10) % 360;
		break;
	case 'y':
		year = (year + 5) % 360;
		break;
	case 'Y':
		year = (year - 5) % 360;
		break;
	case 'v':
		viewChoice++;
		//if (viewChoice > 2 /*numViews*/) viewChoice = 0;
		viewChoice %= 2;
		setViewChoice();
		break;
	case 'a':
		autoMotion = !autoMotion;
		break;
	default:
		break;
	}
	
	glutPostRedisplay();
	reshape(500, 500);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

