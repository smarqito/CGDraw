#pragma once
#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE
#ifndef COLOR_H
#define COLOR_H

#include "cartesian.h"
#include <tinyxml2.h>
#include <math.h>

using namespace tinyxml2;

class Color
{
private:
	float _diffuse[4] = {200.f / 255,200.f / 255.f,200.f / 255.f, 1.f};
	float _ambient[4] = {50.f / 255.f ,50.f / 255.f ,50.f / 255.f , 1.f};
	float _specular[4] = {0.f,0.f,0.f, 1.f};
	float _emissive[4] = {0.f,0.f,0.f, 1.f};
	float _shininess = 0.f;

public:
	Color();
	Color(XMLElement * xml);

	/*
	* Draw Color
	*/
	void _draw();

	/*
	* Getters
	*/
	float* getDiffuse();
	float* getAmbient();
	float* getSpecular();
	float* getEmissive();
	float getShininess();
	
	/*
	* Setters
	*/
	void setDiffuse(float r, float g, float b);
	void setAmbient(float r, float g, float b);
	void setSpecular(float r, float g, float b);
	void setEmissive(float r, float g, float b);
	void setShininess(float value);

};
#endif // !COLOR_H