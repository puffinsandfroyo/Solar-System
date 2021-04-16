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


#include <windows.h>
#include <stdlib.h>
#include "glut.h"
#include <iostream>

#define GlobalAmbientLight 1
#define PositionalLight1 2
#define PositionalLight2 3
//#define DirectionalLight 4

#define Wireframe 5
#define FlatShading 6
#define SmoothShading 7

using namespace std;

float xView = 0, yView = 0.0, zView = 5.0;

static int year = 0, day = 0, viewChoice = 0, lod = 0; 

bool autoMotion = false;
bool globalAmbientLightOn = true, positionalLight1On = true, positionalLight2On = false;

float globalAmbient = 0.2;
float lightX = 0.0, lightY = 0.0, lightZ = 0.0;
float lightDiffuse = 0.9;


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void setViewChoice()
{
	switch (viewChoice)
	{
	case 0: xView = 0.0; yView = 0.0; zView = 5.0; break;
	case 1: xView = 0.0; yView = 5.0; zView = 5.0; break;
	}
	//reshape(500, 500);
	//glutPostRedisplay();
}

void setLighting(void) {
	const GLfloat DIRECTIONAL = 1.0;
	const GLfloat POSITIONAL = 1.0;
	// set global light properties
	GLfloat lmodel_ambient[] = { globalAmbient, globalAmbient, globalAmbient, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat light_position[] = { lightX, lightY, lightZ, DIRECTIONAL };
	GLfloat light_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat light_diffuse[] = { lightDiffuse, lightDiffuse, lightDiffuse, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	// set properties this light 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	//z-buffering
	
	glPushMatrix();

	glColor4f(1.0, 0.84, 0.0, 1.0);	//sun ~ gold
	glutSolidSphere(1.0, 20, 16); // draw sun 
	glPushMatrix();
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0); //Rotate for the year

	glTranslatef(2.0, 0.0, 0.0); //Move away from sun 
	glColor4f(0.0, 0.0, 1.0, 1.0);	//planet ~ blue
	glutSolidSphere(0.3, 10, 8); // draw planet earth
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0); //Rotate planet around y axis 	
	

	glTranslatef(0.50, 0.0, 0.0); //Move away from earth 
	glColor4f(0.961, 0.949, 0.816, 1.0); //moon ~ white
	glutSolidSphere(0.1, 10, 8); //draw moon
	glPopMatrix(); //Move back to the sun origin 

	glRotatef((GLfloat)(((year - 50)%360) ), 0.0, 1.0, 0.0); 
	glTranslatef(3.0, 0.0, 0.0); //Move a little farther out than earth
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0); //rotate day
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glutSolidSphere(0.3, 10, 8);
	glPopMatrix(); // Go back to the origin

	setLighting();
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


void idle() {
	if (autoMotion) {
		//day = (day + 10) % 360;
		year = (year + 5) % 360;
		day = (day + 10) % 360;
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
		viewChoice %= 2;
		setViewChoice();
		break;
	case 'a':
		autoMotion = !autoMotion;
		break;
	case '+':
		lod++;
		lod %= 3;
		break;
	default:
		break;
	}

	glutPostRedisplay();
	reshape(500, 500);
}
void processLightSubmenuEvents(int option) {
	switch (option) {
	case GlobalAmbientLight: if (globalAmbientLightOn == true)
								{
									globalAmbient = 0.2;
								}		
							 else
								{
									globalAmbient = 0.0;
								}
						   globalAmbientLightOn = !globalAmbientLightOn;
						   break;
	case PositionalLight1: break;	
		//star 1?
	case PositionalLight2: break;
		//Star 2?
		//case DirectionalLight:
	}
}
	void processDisplaySubmenuEvents(int option){
		switch(option){
		case Wireframe: break;
		case FlatShading: break;
		case SmoothShading: break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System");
	glEnable(GL_DEPTH_TEST);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);


	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	// create menu
	//int lightSubmenu;
	//lightSubmenu = 
	glutCreateMenu(processLightSubmenuEvents);
	glutAddMenuEntry("Ambient Light", GlobalAmbientLight);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutCreateMenu(processDisplaySubmenuEvents);
	glutAddMenuEntry("Wire Frame", Wireframe);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

