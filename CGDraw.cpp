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
#include "World.h"


using namespace std;
using namespace tinyxml2;

float alpha = 0;
float beta = 0;
float alpha2 = 0;
float beta2 = 0;
float radius = 10;
float radius2 = 0;
float step = 0.1;

float xPosition;
float yPosition;
float zPosition;
float xLookAt;
float yLookAt;
float zLookAt;
float xUp;
float yUp;
float zUp;
float fov;
float near;
float far;

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

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void drawCylinder(float radius, float height, int slices) {
	float step = (2 * M_PI) / slices;
	float alpha = 0;
	float beta = 0;
	// put code to draw cylinder in here
	glBegin(GL_TRIANGLES);
	int x = 0, y = 1, z = 0;
	for (int i = 0; i < slices; i++)
	{
		glColor3f(0, 0, 1);
		glVertex3d(x, y, z);
		glVertex3d(x + radius * cos(beta) * sin(alpha), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha));
		glVertex3d(x + radius * cos(beta) * sin(alpha - step), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha - step));
		// ss
		glColor3f(1, 0, 0);
		glVertex3d(x + radius * cos(beta) * sin(alpha), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha));
		glVertex3d(x + radius * cos(beta) * sin(alpha + step), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha + step));
		glVertex3d(x + radius * cos(beta) * sin(alpha), y + height + radius * sin(beta), z + radius * cos(beta) * cos(alpha));
		alpha -= step;

	}
	y += height;
	for (int i = 0; i < slices; i++)
	{
		glColor3f(0.5, 0.5, 1);
		glVertex3d(x, y, z);
		glVertex3d(x + radius * cos(beta) * sin(alpha), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha));
		glVertex3d(x + radius * cos(beta) * sin(alpha + step), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha + step));
		// triangulo
		glColor3f(0, 1, 0);
		glVertex3d(x + radius * cos(beta) * sin(alpha), y - height + radius * sin(beta), z + radius * cos(beta) * cos(alpha));
		glVertex3d(x + radius * cos(beta) * sin(alpha), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha));
		glVertex3d(x + radius * cos(beta) * sin(alpha - step), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha - step));
		alpha += step;
	}
	glEnd();
}
struct cartz {
	double x, y, z;
};

cartz polartocart(double r, double alpha, double beta) {
	cartz c;
	c.x = r * cos(beta) * sin(alpha);
	c.y = r * sin(beta);
	c.z = r * cos(beta) * cos(alpha);
	return c;
}

double polarx(double r, double alpha, double beta) {
	return r * cos(beta) * sin(alpha);
}

double polary(double r, double alpha, double beta) {
	return r * sin(beta);
}

double polarz(double r, double alpha, double beta) {
	return r * cos(beta) * cos(alpha);
}

void drawCone(float radius, float height, int slices, int stacks) {
	double step = (2 * M_PI) / slices;
	double alpha = 0;
	double beta = atan(height / radius);
	double l = radius / cos(beta);
	double rstep = l / stacks;
	// put code to draw cylinder in here
	glBegin(GL_TRIANGLES);
	int x = 0, y = height, z = 0;
	double r = 0;
	beta = -beta;
	for (int i = 0; i < stacks; i++)
	{
		alpha = 0;
		for (int i = 0; i < slices; i++)
		{
			cartz a = polartocart(r, alpha, beta);
			cartz b = polartocart(r + rstep, alpha, beta);
			cartz c = polartocart(r, alpha + step, beta);
			cartz d = polartocart(r + rstep, alpha + step, beta);
			glVertex3d(a.x, a.y + y, a.z); //a
			glVertex3d(b.x, b.y + y, b.z); //b
			glVertex3d(c.x, c.y + y, c.z); //c

			glVertex3d(b.x, b.y + y, b.z); //b
			glVertex3d(d.x, d.y + y, d.z); //d
			glVertex3d(c.x, c.y + y, c.z); //c


			alpha += step;
		}
		r += rstep;
	}
	y = 0;
	beta = 0;
	for (int i = 0; i < slices; i++)
	{
		glColor3f(0, 0, 1);
		glVertex3d(x, y, z);
		glVertex3d(x + radius * cos(beta) * sin(alpha), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha));
		glVertex3d(x + radius * cos(beta) * sin(alpha - step), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha - step));
		alpha += step;

	}

	glEnd();

}

void drawSphere(double radius, int slices, int stacks) {
	double sst = M_PI / stacks;
	double ssl = 2 * M_PI / slices;
	double beta = -M_PI / 2;
	double alpha = 0;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < stacks; i++)
	{
		for (int i = 0; i < slices; i++)
		{
			cartz a = polartocart(radius, alpha, beta);
			cartz b = polartocart(radius, alpha, beta + sst);
			cartz c = polartocart(radius, alpha + ssl, beta + sst);
			cartz d = polartocart(radius, alpha + ssl, beta);
			glVertex3d(a.x, a.y, a.z); //a
			glVertex3d(b.x, b.y, b.z); //b
			glVertex3d(c.x, c.y, c.z); //c

			glVertex3d(a.x, a.y, a.z); //a
			glVertex3d(c.x, c.y, c.z); //c
			glVertex3d(d.x, d.y, d.z); //d
			alpha += ssl;
		}
		beta += sst;
		alpha = 0;
	}
	glEnd();
}

void drawAxis() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(
		-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f,
		-100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f,
		-100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}

void draw() {
	/*Groups groups = world.getGroups();
	Group g = groups.getGroup();
	list<Models> list = g.getModel();
	auto it = list.begin();
		Models models = *it;
		list<Model> model_list = models.getModels();
		auto model_it = model_list.begin();
		for (int i = 0; i < model_list.size(); i++) {
			advance(model_it, i);
			Model m = *model_it;
			glBegin(m.getType());
			point p;
			for (int j = 0; j < m.size(); j++) {
				p = m.getNextPoint();
				glVertex3d(p.x, p.y, p.z);
			}
			glEnd();

		}
	}*/
}

/*Model read3D(const char* path) {
	XMLDocument doc;
	doc.LoadFile(path);
	XMLElement* pRootElement = doc.FirstChild()->ToElement();
	GLenum type = pRootElement->FindAttribute("type")->IntValue();
	int size = pRootElement->FindAttribute("size")->IntValue();
	Model m = Model(type, size, path);
	XMLElement* pPoint = pRootElement->FirstChildElement("point");
	for (int i = 0; pPoint != NULL; i++) {
		float x = pPoint->FindAttribute("x")->FloatValue();
		float y = pPoint->FindAttribute("y")->FloatValue();
		float z = pPoint->FindAttribute("z")->FloatValue();
		//m.addPoint(x, y, z);
		pPoint = pPoint->NextSiblingElement();
	}
	return m;
}*/



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_LINE);
	// set the camera
	glLoadIdentity();
	float px = radius * cos(beta) * sin(alpha);
	float py = radius * sin(beta);
	float pz = radius * cos(beta) * cos(alpha);
	float dx = radius2 * cos(beta2) * sin(alpha2);
	float dy = radius2 * sin(beta2);
	float dz = radius2 * cos(beta2) * cos(alpha2);

	world._draw_lookAt();
	
	world._draw();

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

void readCamaraSettings(XMLElement* pCamara) {
	XMLElement* pPosition = pCamara->FirstChildElement("position");
	float xPosition = pPosition->FindAttribute("x")->FloatValue();
	float yPosition = pPosition->FindAttribute("y")->FloatValue();
	float zPosition = pPosition->FindAttribute("z")->FloatValue();
	XMLElement* pLookAt = pCamara->FirstChildElement("lookAt");
	float xLookAt = pLookAt->FindAttribute("x")->FloatValue();
	float yLookAt = pLookAt->FindAttribute("y")->FloatValue();
	float zLookAt = pLookAt->FindAttribute("z")->FloatValue();
	XMLElement* pUp = pCamara->FirstChildElement("up");
	float xUp = pUp->FindAttribute("x")->FloatValue();
	float yUp = pUp->FindAttribute("y")->FloatValue();
	float zUp = pUp->FindAttribute("z")->FloatValue();
	XMLElement* pProjection = pCamara->FirstChildElement("projection");
	float fov = pProjection->FindAttribute("fov")->FloatValue();
	float near = pProjection->FindAttribute("near")->FloatValue();
	float far = pProjection->FindAttribute("far")->FloatValue();
	//world.setCamera(xPosition, yPosition, zPosition, xLookAt, yLookAt, zLookAt, xUp, yUp, zUp, fov, near, far);
}

void readGroup(XMLElement* pGroup){
	XMLElement* pModels = pGroup->FirstChildElement("models");
		XMLElement* pModel = pModels->FirstChildElement("model");
		for (; pModel != NULL; pModel = pModel->NextSiblingElement()) {
			char fullPath[100];
			const char* file = pModel->FindAttribute("file")->Value();
			const char* path = "/home/smarqito/test_files_phase_1/";
			strcpy(fullPath, path);
			strcat(fullPath, file);
			//Model m = read3D(fullPath);
		}
}

void readXML() {
	const char* path = "/home/smarqito/test_files_phase_1/test_1_2.xml";
	XMLDocument doc;
	doc.LoadFile(path);
	XMLNode* pRootElement = doc.FirstChild();
	XMLElement* pCamara = pRootElement -> FirstChildElement("camera");
	readCamaraSettings(pCamara);
	XMLElement* pGroup = pRootElement->FirstChildElement("group");
	readGroup(pGroup);
}



int main(int argc, char** argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	readXML();

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
