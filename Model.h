#pragma once
#ifndef MODEL_H
#define MODEL_H

#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE

#include "Normals.h"
#include "Texture.h"
#include "generator/shapes.h"
#include "cartesian/cartesian.h"
#include "Color.h"
#include <string>
#include <tinyxml2.h>
#include <vector>


using namespace tinyxml2;

class Model {

private:
	//t_points _points;
	GLenum _type;
	XMLElement* _xml_model;
	std::string _model_path;
	GLuint* _buffer; // VBO buffers pointers
	GLint* _total_points;
	int _n_buffers;
	Color _color;
	Texture _texture;
	Normals _normals;
	//GLint _total_points; // hold total points to be drawn
		/*
	*/
	void read_points_basic(XMLElement* x_root);
	/*
	*/
	void read_points_patch(XMLElement* x_root);
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
