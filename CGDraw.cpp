#include "CGDraw.h"
#include "generator/shapes.h"
#include <math.h>
#include <iostream>
#include <tuple>
#include <tinyxml2.h>
#include <string>
#include <iterator>

using namespace tinyxml2;

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
	world._draw_projection(ratio);
	//gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

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
	glColor3f(1, 1, 1);
	glEnd();
}

void renderInfo(void) {
	glPushMatrix();
	gluOrtho2D(0, 800, 0, 800);
	glRasterPos2i(10, 0);
	std::string menu = "Ola";
	for (int i = 0; i < menu.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, menu[i]);
	}
	glPopMatrix();
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT, GL_LINE);
	// set the camera
	glLoadIdentity();

	// set lookat world
	world._draw_lookAt();

	// draw world loaded
	world._draw();

	if (drawAxisB) {
		// colocar numa tecla
		drawAxis();
	}
	//renderInfo();
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	Point p;
	switch (c)
	{
	default:
	case 'd':
		world.move_camera_pos(RIGHT);
		break;
	case 'a':
		world.move_camera_pos(LEFT);
		break;
	case 's':
		world.move_camera_pos(BACK);
		break;
	case 'w':
		world.move_camera_pos(FRONT);
		break;
	case '+':
		world.change_scale(1);
		break;
	case '-':
		world.change_scale(-1);
		break;
	case 'u':
		extern bool draw_curves;
		if (draw_curves) {
			draw_curves = false;
		}
		else {
			draw_curves = true;
		}
		break;
	case 'U':
		extern bool draw_derivatives;
		if (draw_derivatives) {
			draw_derivatives = false;
		}
		else {
			draw_derivatives = true;
		}
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
		break;
	case GLUT_KEY_DOWN:
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

bool mouseDown = false;
double mx, my;
void processMouseKeys(int button, int state, int x, int y) {
	//float diffx, diffy;
	if (button == GLUT_LEFT_BUTTON) {
		switch (state)
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

	}
	glutPostRedisplay();
}

void handleMouseMotion(int x, int y) {
	double mxx = mx, myy = my;
	double diffx, diffy;
	diffx = mx - x;
	diffy = my - y;
	mx = x;
	my = y;
	world.move_lookat(diffx / 400, diffy / 400);
	glutPostRedisplay();
}

void init() {
	glEnableClientState(GL_VERTEX_ARRAY);
	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

}

int main(int argc, char** argv) {

	if (argc != 2) {
		std::cout << "./CGDraw world.xml";
	}

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseKeys);
	glutMotionFunc(handleMouseMotion);

	// init
	init();
	glewInit();
	// init world from xml
	world = World(argv[1]);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
