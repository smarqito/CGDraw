#pragma once
#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE
#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include <Point.h>
#include <Light.h>

class DirectionalLight : public Light {

public:
	float _point[4];
	DirectionalLight(int no, XMLElement* xmlElem);
	void _draw();
};

#endif