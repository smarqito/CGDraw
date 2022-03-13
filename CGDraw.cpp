#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <tuple>
#include <tinyxml2.h>
#include <string>
#include <iterator>
#include "generator/shapes.h"
#include "CGDraw.h"

using namespace std;
using namespace tinyxml2;

float alpha = 0;
float beta = 0;
float alpha2 = 0;
float beta2 = 0;
float radius = 5;
float radius2 = 0;
float step = 0.1;

//Inicializar classe world
World world;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	//world._draw_projection(ratio);
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

bool drawAxisB = false;
void drawAxis() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(.3f, 0.0f, 0.0f);
	glVertex3f(
		-1000.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Y Axis in Green
	glColor3f(0.0f, .3f, 0.0f);
	glVertex3f(0.0f,
		-1000.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, .3f);
	glVertex3f(0.0f, 0.0f,
		-1000.0f);
	glVertex3f(0.0f, 0.0f, .0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, .0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glEnd();
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_LINE);
	// set the camera
	glLoadIdentity();


	//define camera config
	//world._draw_lookAt();
	//float px = radius * cos(beta) * sin(alpha);
	//float py = radius * sin(beta);
	//float pz = radius * cos(beta) * cos(alpha);
	//float dx = radius2 * cos(beta2) * sin(alpha2);
	//float dy = radius2 * sin(beta2);
	//float dz = radius2 * cos(beta2) * cos(alpha2);

	//world.set_camera_pos(px, py, pz);
	world._draw_lookAt();

	// draw world loaded
	world._draw();

	if (drawAxisB) {
		// colocar numa tecla
		drawAxis();
	}
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

	switch (c)
	{
	default:
	case 'w':
		beta += step;
		break;
	case 's':
		beta -= step;
		break;
	case 'a':
		alpha -= step;
		break;
	case 'd':
		alpha += step;
		break;
	case 'j':
		radius += 1;
		break;
	case 'k':
		radius -= 1;
		break;
	case 'p':
		if (drawAxisB) {
			drawAxisB = false;
		}
		else {
			drawAxisB = true;
		}
		break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key)
	{
	case GLUT_KEY_UP:
		radius2 += step;
		break;
	case GLUT_KEY_DOWN:
		radius2 -= step;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

bool mouseDown = false;
int mx, my;
void processMouseKeys(int button, int state, int x, int y) {
	//float diffx, diffy;
	switch (button)
	{
	case GLUT_DOWN:
		if (mouseDown) {
		}
		else {
			mouseDown = true;
			mx = x;
			my = y;
		}
		break;
	case GLUT_UP:
		mouseDown = false;
		my = y;
		mx = x;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void handleMouseMotion(int x, int y) {
	float diffx, diffy;
	diffx = mx - x;
	diffy = my - y;
	mx = x;
	my = y;
	alpha2 += (diffx / (800));
	beta2 -= (diffy / (800));
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	if (argc != 2) {
		cout << "./CGDraw world.xml";
	}
	world = World(argv[1]);

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");


	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseKeys);
	glutMotionFunc(handleMouseMotion);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
