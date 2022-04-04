#pragma once
#ifndef MODEL_H
#define MODEL_H

#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE

#include "generator/shapes.h"
#include "cartesian/cartesian.h"
#include <string>
#include <tinyxml2.h>
#include <vector>


using namespace std;
using namespace tinyxml2;

class Model {

private:
	//t_points _points;
	GLenum _type;
	XMLElement* _xml_model;
	string _model_path;
	GLuint _buffer; // VBO buffer pointer
	GLint _total_points; // hold total points to be drawn
	//texture texture; // phase not 1
	//color color; // phase not 1
	void read_points();
public:
	Model(XMLElement* xml_elem);

	void _init();

	GLenum getType();

	char* getFilename();

	//int size();

	//bool add_point(double x, double y, double z);


	void _draw();
	//void build_vbo();
};

#endif // !MODEL_H
