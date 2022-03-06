// CGDraw.cpp : Defines the entry point for the application.
//
#include <GL/glut.h>
#include "CGDraw.h"

#include <math.h>
#include <map>

using namespace std;

GLfloat ex = 5, ez = 5;
GLfloat height = 1;
GLfloat angle = 0;
GLfloat tx = 0, ty = 0, tz = 0;
GLfloat rx = 0, ry = 1, rz = 0;
GLenum face = GL_FRONT;
GLenum mode = GL_LINE;
float step = 0.5;

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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderAxis(void) {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(face, mode);

	// set the camera
	glLoadIdentity();
	gluLookAt(ex, 2.0, ez,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	renderAxis();
	// put the geometric transformations here
	glTranslatef(tx, ty, tz);
	glRotatef(angle, rx, ry, rz);
	// put drawing instructions here


	glBegin(GL_TRIANGLES);
	// A
	glColor3f(1.5f, 1.0f, 2.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, height, 0.0f);
	// B
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, height, 0.0f);
	// C
	glColor3f(2.0f, -1.0f, 5.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, height, 0.0f);
	// D
	glColor3f(0.0f, 0.0f, 2.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, height, 0.0f);
	// base 1
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	// base 2
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd();

	// End of frame
	glutSwapBuffers();
}

void handle_space(void) {
	angle += 1;
}

// write function to process keyboard events
void handle_keys(unsigned char key, int x, int y) {
	std::map<char, void(*)()> mapa = {
		{' ', handle_space}
	};
	switch (key)
	{
	case ' ':
		mapa[' ']();
		break;
	case 'w':
		tz -= step;
		break;
	case 'a':
		tx -= step;
		break;
	case 's':
		tz += step;
		break;
	case 'd':
		tx += step;
		break;
	case ',':
		height -= step;
		break;
	case '.':
		height += step;
		break;
	case '1':
		mode = GL_FILL;
		break;
	case '2':
		mode = GL_LINE;
		break;
	case '3':
		mode = GL_POINT;
		break;
	case 'z':
		rz += 1;
		angle = 0;
		break;
	case 'Z':
		rz -= 1;
		angle = 0;
		break;
	case 'x':
		rx += 1;
		angle = 0;
		break;
	case 'X':
		rx -= 1;
		angle = 0;
		break;
	case 'y':
		ry += 1;
		angle = 0;
		break;
	case 'Y':
		ry -= 1;
		angle = 0;
		break;
	case 'k':
		ez -= step;
		break;
	case 'j':
		ez += step;
		break;
	case 'l':
		ex += step;
		break;
	case 'h':
		ex -= step;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}





int main(int argc, char** argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(handle_keys);


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
