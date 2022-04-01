#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "generator/shapes.h"
#include <string>
#include "cartesian/cartesian.h"
#include <tinyxml2.h>
#include <vector>


using namespace std;
using namespace tinyxml2;

class Model {

private:
	t_points _points;
	GLenum _type;
	XMLElement* _xml_model;
	string _model_path;
	GLuint buffer;
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
	void build_vbo();
};

#endif // !MODEL_H
