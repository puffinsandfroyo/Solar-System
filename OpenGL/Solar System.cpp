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

/*texture mapping resources:
https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231
https://stackoverflow.com/questions/31799670/applying-map-of-the-earth-texture-a-sphere
https://www.codeguru.com/cpp/g-m/opengl/texturemapping/article.php/c5589/A-Texture-Mapping-Technique-Using-OpenGL.htm
http://planetpixelemporium.com/earth.html
http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html
*/

#include <windows.h>
#include <stdlib.h>
#include "glut.h"
#include <iostream>

#define GlobalAmbientLight 1
#define PositionalLight1 2
#define PositionalLight2 3
//#define DirectionalLight 4

#define WireFrame 5
#define SolidFrame 6
#define FlatShading 7
#define SmoothShading 8

using namespace std;

float xView = 0, yView = 0.0, zView = 5.0;

static int year = 0, day = 0, viewChoice = 0, lod = 0; 

bool autoMotion = false;
bool globalAmbientLightOn = true, positionalLight1On = false, positionalLight2On = false;
bool wireframe = false, solidframe = true, flatshading = false, smoothshading = true;


float globalAmbient = 0.2;
float lightX = 0.0, lightY = 0.0, lightZ = 0.0;
float lightDiffuse = 0.9;

int width = 500, height = 500;

void setNightSky(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	int numPoints = 3000;

	glPointSize(5.0);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	//for (int x = 0; x < numPoints; x++) {
	//	glVertex3i(rand() % -10, rand() % height, rand() % width);
	//}
	glVertex3i(0, 5, 5);
	glEnd();

	glFlush();
	//glutPostRedisplay();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glLoadIdentity();
	setNightSky(); //This can't sit in init. 
	//We would need to make an array of stars or something and put it in display.
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
	GLfloat light_ambient[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_diffuse[] = { lightDiffuse, lightDiffuse, lightDiffuse, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	// set properties this light 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	if (positionalLight1On == true){
	GLfloat light_position[] = { 8, 8, 8, DIRECTIONAL };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { lightDiffuse, lightDiffuse, lightDiffuse, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	//glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	}

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	//z-buffering
	

	glPushMatrix();

	glColor4f(1.0, 0.84, 0.0, 1.0);	//sun ~ gold
	if (solidframe == true) {
		glutSolidSphere(1.0, 20, 16); // draw sun 
	}
	else if (wireframe == true) {
		glutWireSphere(1.0, 20, 18);
	}
								  //glPushMatrix();
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0); //Rotate for the year
	glPushMatrix();
	//Mercury (dark brown)
	//Venus (golden)


	glTranslatef(4.5, 0.0, 0.0); //Move away from sun 
	glColor4f(0.0, 0.0, 1.0, 1.0);	//planet ~ blue
	if (solidframe == true) {
		glutSolidSphere(0.3, 10, 8); // draw planet earth
	}
	else if(wireframe == true) {
		glutWireSphere(0.3, 10, 8);
	}
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0); //Rotate planet around y axis 	
	

	glTranslatef(0.50, 0.0, 0.0); //Move away from earth 
	glColor4f(0.961, 0.949, 0.816, 1.0); //moon ~ white
	if (solidframe == true) {
		glutSolidSphere(0.1, 10, 8);
	}
	else if (wireframe == true) {
		glutWireSphere(0.1, 10, 8);//draw moon
	}
	glPopMatrix(); //Move back to the sun origin 

	glTranslatef(1.5, 0.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glColor4f(0.5, 0.2, 0.1, 1.0);
	if (solidframe == true) {
		glutSolidSphere(0.1, 10, 8);
	}
	else if (wireframe == true) {
		glutWireSphere(0.1, 10, 8);
	}
	//glPopMatrix();

	//glRotatef((GLfloat)(((year)%360) ), 0.0, 1.0, 0.0); 
	glTranslatef(5.5, 0.0, 0.0); //Move a little farther out than earth
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0); //rotate day
	glColor4f(1.0, 0.0, 0.0, 1.0);
	if (solidframe == true) {
		glutSolidSphere(0.3, 10, 8);
	}
	else if (wireframe == true) {
		glutWireSphere(0.3, 10, 8);
	}
	glPopMatrix(); // Go back to the origin
	
	//Jupiter (light brown)
	//Saturn (orange yellow)
	//Uranus (cyan)
	//Neptune (light blue)
	//Pluto (small light brown)

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
		year = (year + 1) % 360;
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
		zView++;
		//lod++;
		//lod %= 3;
		break;
	default:
		break;
	}

	glutPostRedisplay();
	reshape(width, height);
}

void specialInput(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP: printf("rotate y up"); break;		//implement zoom as scroll wheel?
		case GLUT_KEY_DOWN: printf("rotate y down"); break;
		case GLUT_KEY_LEFT: printf("rotate x left"); break;
		case GLUT_KEY_RIGHT: printf("rotate x right"); break;
	}
}

void mouse(int button, int state, int x, int y) {
	if ((button == 4) || (button == 5))
		//scroll conditions ~ zoom in and out ~ should use glutMouseWheelFunc instead?
		;
}

void processLightSubmenuEvents(int option) {
	switch (option) {
	case GlobalAmbientLight:	if (globalAmbientLightOn)	globalAmbient = 0.2;		
								else globalAmbient = 0.0;
								globalAmbientLightOn = !globalAmbientLightOn;
								break;
	case PositionalLight1:		positionalLight1On = !positionalLight1On;
								break;	
								//star 1?
	case PositionalLight2:		if (positionalLight2On);
								else;
								positionalLight2On = !positionalLight2On;
								break;
								//Star 2?
	//case DirectionalLight:
	}
}
	void processDisplaySubmenuEvents(int option){
		switch(option){
		case WireFrame:		wireframe = true;
							solidframe = false;
							break;
		case SolidFrame:	wireframe = false;
							solidframe = true;
							break;
		case FlatShading:	flatshading = true;
							smoothshading = false; 
							break;
		case SmoothShading:	flatshading = false; 
							smoothshading = true; 
							break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System");
	glEnable(GL_DEPTH_TEST);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);


	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutSpecialFunc(specialInput);
	glutIdleFunc(idle);

	// create menu
	//int lightSubmenu;
	//lightSubmenu = 
	glutCreateMenu(processLightSubmenuEvents);
	glutAddMenuEntry("Ambient Light", GlobalAmbientLight);
	glutAddMenuEntry("Positional light 1", positionalLight1On);
	glutAddMenuEntry("Positional light 2", positionalLight2On);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutCreateMenu(processDisplaySubmenuEvents);
	glutAddMenuEntry("Wire Frame", WireFrame);
	glutAddMenuEntry("Solid Frame", SolidFrame);
	glutAddMenuEntry("Flat Shading", FlatShading);
	glutAddMenuEntry("Smooth Shading", SmoothShading);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

