#include "Light.h"
#include "Point.h"
#include <gl/freeglut.h>

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

class PointLight : public Light {
private:
	float _point[4];
public:
	PointLight(int light_no , XMLElement* xmlElem);
	void _draw();
};

#endif
