#include "PointLight.h"

PointLight::PointLight(int light_no, XMLElement* xmlElem) : Light(light_no) {
	_point[0] = xmlElem->FloatAttribute("posX");
	_point[1] = xmlElem->FloatAttribute("posY");
	_point[2] = xmlElem->FloatAttribute("posZ");
	_point[3] = 1.f;
}

void PointLight::_draw() {
	glLightfv(getLightNo(), GL_POSITION, _point);
}