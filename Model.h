#pragma once
#include <GL/glut.h>
#include "generator/shapes.h"
#include <string.h>
#include "cartesian/cartesian.h"
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

class Model {

private:
	t_points _points;
	GLenum _type;
	XMLElement* _xml_model;
	char* _model_path;
	//texture texture; // phase not 1
	//color color; // phase not 1
	void read_points();
public:
	Model(XMLElement* xml_elem);

	void _init();

	GLenum getType();

	char* getFilename();

	int size();

	bool add_point(double x, double y, double z);

	point get_next_point();

	void _draw();
};
