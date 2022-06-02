#pragma once
#include <gl/freeglut.h>

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