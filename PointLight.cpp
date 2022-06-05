#include "PointLight.h"

PointLight::PointLight(int light_no, XMLElement* xmlElem) : Light(light_no) {
	_point[0] = xmlElem->FloatAttribute("posx");
	_point[1] = xmlElem->FloatAttribute("posy");
	_point[2] = xmlElem->FloatAttribute("posz");
	_point[3] = 1.f;
}

void PointLight::_draw() {
	glLightfv(getLightNo(), GL_POSITION, _point);
}