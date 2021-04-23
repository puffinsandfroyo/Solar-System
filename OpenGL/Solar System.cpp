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

float xView = 0, yView = 5.0, zView = 12.0;
//float rho, theta, phi;	//polar coord transformation

static int year = 0, day = 0, viewChoice = 0, lod = 0; 

bool autoMotion = false;
bool globalAmbientLightOn = true, positionalLight1On = true, positionalLight2On = false;
bool wireframe = false, solidframe = true, flatshading = false, smoothshading = true;


float globalAmbient = 0.2;
float lightX = 0.0, lightY = 0.0, lightZ = 0.0;
float lightDiffuse = 0.9;

char * WireFrameName = "Wire Frame", *FlatShadingName = "Solid Frame & Flat Shading * ", *SmoothShadingName = "Solid Frame & Smooth Shading ";
char* GlobalAmbientLightName = "Global Ambient Light *", * PositionalLight1Name = "Positional Light 1 *", * PositionalLight2Name = "Positional Light 2";

int width = 1000, height = 500;

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
	//setNightSky(); //This can't sit in init. 
	//We would need to make an array of stars or something and put it in display.
}

void setViewChoice()
{
	switch (viewChoice)
	{
	case 0: xView = 0, yView = 5.0, zView = 12.0; 
		lod = 0; //bare bones solarsystem
		break;

	case 1: xView = 0.0; yView = 5.0; zView = 5.0;
		lod = 1; //Add orbital lines
		break;

	case 2: xView = 0.0; yView = 5.0; zView = 5.0; 
		lod = 2; //Add moons and day cycles
		break;

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
		//glPointSize(5.0);
		//glColor3b(1.0, 1.0, 1.0);
		//glBegin(GL_POINTS);
		//glVertex3d(8, 8, 8);
		//glEnd();
		GLfloat light1_position[] = { 8, 8, 8, POSITIONAL };
		GLfloat light1_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat light1_diffuse[] = { lightDiffuse, lightDiffuse, lightDiffuse, 1.0 };
		GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };

		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	}

	if (positionalLight2On == true) {
		GLfloat light_position[] = { 0, 0, 10, POSITIONAL };
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
	

	glPushMatrix(); //Identity (Matrix 0) Now editing Matrix 1
	//--Make Sun--//
	{
		glColor4f(1.0, 0.84, 0.0, 1.0);	//sun ~ gold
		if (solidframe == true) {
			glutSolidSphere(1.0, 20, 16); // draw sun 
		}
		else if (wireframe == true) {
			glutWireSphere(1.0, 20, 18);
		}
		//glPushMatrix();
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0); //Matrix 1 (sun) (rotate)
	}
	glPushMatrix(); //Working on Matrix 2 (planet) (rotate//)
	
	//Mercury (dark brown)
	{
		//glTranslatef(4.5, 0.0, 0.0);
		glRotatef(year * 1.5, 0.0, 1.0, 0.0);
		glTranslatef(1.5, 0.0, 0.0); //Matrix 2(rotate//translate)
		glColor4f(0.5, 0.2, 0.1, 1.0);
		if (lod == 2) {
		glRotatef((GLfloat)day/58.66, 0.0, 1.0, 0.0); //Matrix 2(rotate// translate, rotate )
		}
		if (solidframe == true) {
			glutSolidSphere(0.1, 10, 8);
		}
		else if (wireframe == true) {
			glutWireSphere(0.1, 10, 8);
		}

	}
	glPopMatrix(); //Matrix 1(rotate)
	glPushMatrix();//Now working on Matrix 2(rotate//)

	//Venus (golden)
	{
		glRotatef(year * 1.2, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0); //Matrix 2(rotate// translate)
		if (lod == 2) {
			glRotatef((GLfloat)day/243, 0.0, 1.0, 0.0); //Matrix 2(rotate// translate, rotate )
		}
		glColor4f(0.3, 0.3, 0.1, 1.0);
		if (solidframe == true) {
			glutSolidSphere(0.1, 10, 8);
		}
		else if (wireframe == true) {
			glutWireSphere(0.1, 10, 8);
		}
	}
	glPopMatrix();  //Matrix 1(rotate)
	glPushMatrix(); //Now working on Matrix 2(rotate//)

	//--Make Earth and moon--//
	{
		glTranslatef(2.7, 0.0, 0.0); //Matrix 2 (rotate// translate)
		glColor4f(0.0, 0.0, 0.8, 1.0);
		glPushMatrix(); //Matrix 3 (rotate// translate//)
		if (lod == 2) {
			glRotatef((GLfloat)day, 0.0, 1.0, 0.0); //Matrix 3(rotate// translate// rotate )
		}
		if (solidframe == true) {
			glutSolidSphere(0.3, 10, 8);
		}
		else if (wireframe == true) {
			glutWireSphere(0.3, 10, 8);
		}
		glPopMatrix();					//Matrix 2 (moon) (rotate// translate)

		if (lod == 2) {
			glRotatef((GLfloat)day / 27, 0.0, 1.0, 0.0); //Matrix 3 (rotate// translate// rotate)	


			//Make Moon - only if lod == greatest detail?
			{glTranslatef(0.50, 0.0, 0.0); //Matrix 3 (rotate// translate// rotate, translate) 
			glColor4f(0.961, 0.949, 0.816, 1.0);
			if (solidframe == true) {
				glutSolidSphere(0.1, 10, 8);
			}
			else if (wireframe == true) {
				glutWireSphere(0.1, 10, 8);//draw moon
			}
			}
		}
	}
	glPopMatrix(); //Matrix 2(rotate// translate//)
	glPopMatrix(); //Matrix 1 (rotate)
	glPushMatrix(); //Matrix 2(rotate//) 
	
	 //--Make Mars--//
	{
		glRotatef(year * 0.8, 0.0, 1.0, 0.0);
		glTranslatef(3.9, 0.0, 0.0); //Matrix 2(rotate// translate)
		glColor4f(0.8, 0.0, 0.0, 1.0);
		if (lod == 2) {
			glRotatef((GLfloat)day/1.04, 0.0, 1.0, 0.0); //Matrix 2(rotate// translate, rotate )
		}
		if (solidframe == true) {
			glutSolidSphere(0.3, 10, 8);
		}
		else if (wireframe == true) {
			glutWireSphere(0.3, 10, 8);
		}
		
	}

	glPopMatrix();
	
	glPushMatrix();//Now working on Matrix 2(rotate//)

	//--Make Jupiter--// (light brown)
	{
	glRotatef(year * 0.6, 0.0, 1.0, 0.0);
		glTranslatef(5.5, 0.0, 0.0); //Matrix 2(rotate//translate)
		glColor4f(0.5, 0.2, 0.1, 1.0);
		if (lod == 2) {
			glRotatef((GLfloat)day/0.416, 0.0, 1.0, 0.0); //Matrix 2(rotate// translate, rotate )
		}
		if (solidframe == true) {
			glutSolidSphere(0.8, 10, 8);
		}
		else if (wireframe == true) {
			glutWireSphere(0.8, 10, 8);
		}
		
	}
	glPopMatrix();

	glPushMatrix();//Now working on Matrix 2(rotate//)

	//Saturn (orange yellow)
	{glRotatef(year*0.4, 0.0, 1.0, 0.0);
		glTranslatef(7.75, 0.0, 0.0); //Matrix 2(rotate//translate)
		glColor4f(0.3, 0.2, 0.2, 1.0);
		if (lod == 2) {
			glRotatef((GLfloat)day/0.46, 0.0, 1.0, 0.0); //Matrix 2(rotate// translate, rotate )
		}
		if (solidframe == true) {
			glutSolidSphere(0.6, 10, 8);
			glPushMatrix();
			glRotated(90, 1, 0, 0);
			glColor4f(0.3, 0.2, 0.2, 1.0);
			//could we alter alpha here to make the rings more transparent?
			glutSolidTorus(0.06, 0.8, 4, 12);

			glPopMatrix();
		}
		else if (wireframe == true) {
			glutWireSphere(0.8, 10, 8);
			glutWireTorus(0.06, 0.8, 4, 12);
		}
		
	}
	glPopMatrix();

	glPushMatrix();//Now working on Matrix 2(rotate//)

	//--Make Uranus--// (cyan)
	{
		glRotatef(year * 0.2, 0.0, 1.0, 0.0);
		glTranslatef(9.15, 0.0, 0.0); //Matrix 2(rotate//translate)
		glColor4f(0.02, 0.59, 0.62, 1.0);
		if (lod == 2) {
			glRotatef((GLfloat)day/0.7, 0.0, 1.0, 0.0); //Matrix 2(rotate// translate, rotate )
		}
		if (solidframe == true) {
			glutSolidSphere(0.6, 10, 8);
		}
		else if (wireframe == true) {
			glutWireSphere(0.6, 10, 8);
		}
		
	}
	glPopMatrix();

	glPushMatrix();//Now working on Matrix 2(rotate//)

	//--Make Neptune--// (light blue)
	{
		glRotatef(year * 0.1, 0.0, 1.0, 0.0);
		glTranslatef(10.65, 0.0, 0.0); //Matrix 2(rotate//translate)
		glColor4f(0.31, 0.7, 0.89, 1.0);
		if (lod == 2) {
			glRotatef((GLfloat)day/0.66, 0.0, 1.0, 0.0); //Matrix 2(rotate// translate, rotate )
		}
		if (solidframe == true) {
			glutSolidSphere(0.7, 10, 8);
		}
		else if (wireframe == true) {
			glutWireSphere(0.7, 10, 8);
		}
	}
	//Pluto (small light brown)
	glPopMatrix();

	glPushMatrix();//Now working on Matrix 2(rotate//)

	//--Make Pluto--// (light brown)
	{
		glRotatef(year * 0.05, 0.0, 1.0, 0.0);
		glTranslatef(12.0, 0.0, 0.0); //Matrix 2(rotate//translate)
		glColor4f(0.5, 0.2, 0.1, 1.0);
		if (lod == 2) {
			glRotatef((GLfloat)day, 0.0, 1.0, 0.0); //Matrix 2(rotate// translate, rotate )
		}
		if (solidframe == true) {
			glutSolidSphere(0.2, 10, 8);
		}
		else if (wireframe == true) {
			glutWireSphere(0.2, 10, 8);
		}
		
	}

	glPopMatrix(); //Matrix 1(rotate)
	glPopMatrix(); // Go back to the origin
	setLighting();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(xView, yView, zView, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void idle() {
	if (autoMotion) {
		//day = (day + 10) % 360;
		year = (year + 1);// % 360;
		day = (day + 30);// % 360;
		Sleep(50);
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		day = (day + 10);// % 360;
		break;
	case 'D':
		day = (day - 10);// % 360;
		break;
	case 'y':
		year = (year + 5);// % 360;
		break;
	case 'Y':
		year = (year - 5);// % 360;
		break;
	case 'v':
		viewChoice++;
		viewChoice %= 3;
		setViewChoice();
		break;
	case 'a':
		autoMotion = !autoMotion;
		break;
	case '+':
		lod++;
		lod %= 3;
		break;
	case 'i':
		if (viewChoice == 0) {
			zView--;
			if (zView < 2)
				zView = 2;
		}
		if (viewChoice == 1) {
			yView--; zView--;
			if (yView < 2 && zView < 2) {
				yView = 2; zView = 2;
			}
		}
		if (zView > 8) lod = 0;
		if (zView > 4 && zView < 7) lod = 1;
		if (zView < 5) lod = 2;
		break;
	case 'o':
		if (viewChoice == 0) {
			zView++;
			if (zView > 12) zView = 12;
		}
		if (viewChoice == 1) {
			yView++; zView++;
			if (yView > 10 && zView > 10) {
				yView = 10; zView = 10;
			}	
		}
		if (zView > 8) lod = 0;
		if (zView > 4 && zView < 7) lod = 1;
		if (zView < 5) lod = 2;
		break;
	case '.':
		xView = 0; yView = 5.0; zView = 12.0;
		year = 0; day = 0; viewChoice = 0; lod = 0;
		autoMotion = false;
		globalAmbientLightOn = true; positionalLight1On = true; positionalLight2On = false;
		wireframe = false; solidframe = true; flatshading = false; smoothshading = true;
		globalAmbient = 0.2; lightX = 0.0; lightY = 0.0; lightZ = 0.0;
		lightDiffuse = 0.9;
		width = 1000; height = 500;
		break;
	default:

		break;
	}

	glutPostRedisplay();
	reshape(width, height);
}

void specialInput(int key, int x, int y) {
	switch (key) {
		//implement zoom as 'i' (in) and 'o' (out)?
		case GLUT_KEY_UP:		if (viewChoice == 0) yView++; if (viewChoice == 1) zView++; /*printf("rotate y up");*/ break;
		case GLUT_KEY_DOWN:		if (viewChoice == 0) yView--; if (viewChoice == 1) zView--; /*printf("rotate y down");*/ break;
		case GLUT_KEY_LEFT:		xView--; /*printf("rotate x left");*/ break;
		case GLUT_KEY_RIGHT:	xView++; /*printf("rotate x right");*/ break;
	}
	glutPostRedisplay();
	reshape(width, height);
}

void processLightSubmenuEvents(int option) {
	switch (option) {
	case GlobalAmbientLight:	globalAmbientLightOn = !globalAmbientLightOn;
		if (globalAmbientLightOn) {
			globalAmbient = 0.2;
			GlobalAmbientLightName = "Global Ambient Light *";
		}
		else {
			globalAmbient = 0.0;
			GlobalAmbientLightName = "Global Ambient Light";
		}

		break;
	case PositionalLight1:		positionalLight1On = !positionalLight1On;
		if (positionalLight1On) {
			PositionalLight1Name = "Positional Light 1 *";
		}
		else(PositionalLight1Name = "Positional Light 1");
		break;
		//star 1
	case PositionalLight2:	positionalLight2On = !positionalLight2On;
		if (positionalLight2On) {
			PositionalLight2Name = "Positional Light 2 *";
		}
		else; {
			PositionalLight2Name = "Positional Light 2";
		}


		break;
	}
	glutChangeToMenuEntry(1, GlobalAmbientLightName, 1); glutChangeToMenuEntry(2, PositionalLight1Name, 2); glutChangeToMenuEntry(3, PositionalLight2Name, 3);
	glutPostRedisplay();	//star 2
//case DirectionalLight:
	
}

void processDisplaySubmenuEvents(int option){
	switch (option) {
	case WireFrame:		wireframe = true;
		solidframe = false;
		WireFrameName = "Wire Frame*"; FlatShadingName = "Solid Frame & Flat Shading"; SmoothShadingName = "Solid Frame & Smooth Shading";
		break;
	case FlatShading:	flatshading = true;
		smoothshading = false;
		wireframe = false;
		solidframe = true;
		glShadeModel(GL_FLAT);
		WireFrameName = "Wire Frame"; FlatShadingName = "Solid Frame & Flat Shading* "; SmoothShadingName = "Solid Frame & Smooth Shading";
		break;
	case SmoothShading:	flatshading = false;
		smoothshading = true;
		wireframe = false;
		solidframe = true;
		glShadeModel(GL_SMOOTH);
		WireFrameName = "Wire Frame"; FlatShadingName = "Solid Frame & Flat Shading"; SmoothShadingName = "Solid Frame & Smooth Shading*";
		break;
	}
	glutChangeToMenuEntry(1, WireFrameName, 5); glutChangeToMenuEntry(2, FlatShadingName, 7); glutChangeToMenuEntry(3, SmoothShadingName, 8);
	
	glutPostRedisplay();
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
	glutSpecialFunc(specialInput);
	glutIdleFunc(idle);

	// create menu
	//int lightSubmenu;
	//lightSubmenu = 
	int lightmenu = glutCreateMenu(processLightSubmenuEvents);
	glutAddMenuEntry(GlobalAmbientLightName, GlobalAmbientLight);
	glutAddMenuEntry(PositionalLight1Name, PositionalLight1);
	glutAddMenuEntry(PositionalLight2Name, PositionalLight2);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	
	int displaymenu = glutCreateMenu(processDisplaySubmenuEvents);
	glutAddMenuEntry(WireFrameName, WireFrame);
	//glutAddMenuEntry("Solid Frame", SolidFrame);
	glutAddMenuEntry(FlatShadingName, FlatShading);
	glutAddMenuEntry(SmoothShadingName, SmoothShading);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

