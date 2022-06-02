#pragma once
#ifndef NORMALS_H
#define NORMALS_H
#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE
#include <tinyxml2.h>
#include <vector>

using namespace tinyxml2;

class Normals
{
private:
	GLuint* _buffer;
	XMLElement* _xml_element;
public:
	Normals();
	Normals(XMLElement* xml_elem);
	void init();
	void _draw();
};
#endif
