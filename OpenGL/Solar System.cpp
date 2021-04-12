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
#include <stdlib.h>
#include "glut.h"
#include <iostream>
using namespace std;

bool lightOn = true;
float globalAmbient = 0.2;
int quadrant = 1;
float lightX = 1.0, lightY = 1.0, lightZ = 1.0;
int matSpecChoice = 1;
int matColChoice = 1;
int shapeChoice = 1;
float matSpecR = 1.0, matSpecG = 1.0, matSpecB = 1.0;
float matAmbientR = 0.2, matAmbientG = 0.2, matAmbientB = 0.2;
float matDiffuseR = 0.8, matDiffuseG = 0.8, matDiffuseB = 0.8;
float matShini = 64.0;      // [0.0, 128.0]  higher -> smaller & brighter
float lightDiffuse = 0.8;
bool smoothShade = true;

void setMaterials(void)
{
	matAmbientR = 0.2; matAmbientG = 0.2; matAmbientB = 0.2;
	matDiffuseR = 0.8; matDiffuseG = 0.8; matDiffuseB = 0.8;
	matShini = 64.0;
	

	GLfloat mat_ambient[] = { matAmbientR, matAmbientG, matAmbientB, 1.0 };
	GLfloat mat_diffuse[] = { matDiffuseR, matDiffuseR, matDiffuseR, 1.0 };
	GLfloat mat_specular[] = { matSpecR, matSpecG, matSpecB, 1.0 };
	GLfloat mat_shininess[] = { matShini };

	// set material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

	void setLighting(void)
	{
		const GLfloat DIRECTIONAL = 0.0;

		switch (quadrant)
		{
		case 1: lightX = 1.0;  lightY = 0.0;  lightZ = 0.0;  break;
		case 2: lightX = 1.0;  lightY = -1.0;  lightZ = 1.0;  break;
		case 3: lightX = -1.0;  lightY = 1.0;  lightZ = 1.0;  break;
		case 4: lightX = -1.0;  lightY = -1.0;  lightZ = 1.0;  break;
		case 5: lightX = 1.0;  lightY = 1.0;  lightZ = -1.0;  break;
		case 6: lightX = 1.0;  lightY = -1.0;  lightZ = -1.0;  break;
		case 7: lightX = -1.0;  lightY = 1.0;  lightZ = -1.0;  break;
		case 0: lightX = -1.0;  lightY = -1.0;  lightZ = -1.0;  break;

		}

		// set global light properties
		GLfloat lmodel_ambient[] = { globalAmbient, globalAmbient, globalAmbient, 1.0 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

		GLfloat light_position[] = { lightX, lightY, lightZ, DIRECTIONAL };
		GLfloat light_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
		GLfloat light_diffuse[] = { lightDiffuse, lightDiffuse, lightDiffuse, 1.0 };
		GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

		// set properties this light 
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

		if (lightOn)
			glEnable(GL_LIGHT0);
		else
			glDisable(GL_LIGHT0);

	}

	void myKeyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case '$':  	smoothShade = smoothShade ? false : true;
			break;

		case 'o':		lightOn = lightOn ? false : true;
			break;

		case 'q':		quadrant += 1;
			quadrant %= 8;
			break;

		case '<':		if (lightDiffuse > 0.1)
		{
			lightDiffuse -= 0.1;
		}
				break;

		case '>':     if (lightDiffuse < 1)
		{
			lightDiffuse += 0.1;
		}
				break;

		case '+':		if (globalAmbient < 1)//change value still
		{
			globalAmbient += 0.1;
		}
				break;
		case 'c':		matColChoice++;
			matColChoice %= 2;
		}

		glutPostRedisplay();
	}

	void init(void)
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}

	void display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		setMaterials();
		setLighting();

		if (smoothShade)
			glShadeModel(GL_SMOOTH);
		else
			glShadeModel(GL_FLAT);

		glutSolidSphere(1.0, 40, 32);
		glTranslated(0.5, 0.5, 0.5);
		glutSolidSphere(1.0, 40, 30);

		glFlush();
	}

	void reshape(int w, int h)
	{
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (w <= h)
			glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
				1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
		else
			glOrtho(-1.5 * (GLfloat)w / (GLfloat)h,
				1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	int main(int argc, char** argv)
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(500, 500);
		glutInitWindowPosition(100, 100);
		glutCreateWindow(argv[0]);
		init();
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(myKeyboard);
		glutMainLoop();
		return 0;
	}
