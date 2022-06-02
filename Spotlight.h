#pragma once
#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <Light.h>

class Spotlight : public Light {

private:
	float _point[4];
	float _dir[4];
	float _cutoff;

public:
	Spotlight(int no, XMLElement* xmlElem);
	void _draw();
};

#endif
