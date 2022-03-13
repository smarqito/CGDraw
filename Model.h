#pragma once
#include <GL/glut.h>
#include "generator/shapes.h"
#include <string.h>
#include "cartesian/cartesian.h"

class Model {

private:
	std::vector<t_points> points;
	GLenum type;
	XMLElement xml_elem;
	texture texture;
	color color;

public:
	Model(GLenum type, int size, XMLElement* xml_elem);

	void _init();

	GLenum getType();

	string getFilename();

	int size();

	bool add_point(double x, double y, double z);

	point get_next_point();

	void _draw();
};
