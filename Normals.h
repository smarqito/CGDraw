#pragma once
#ifndef NORMALS_H
#define NORMALS_H
#include <GL/glut.h>
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
