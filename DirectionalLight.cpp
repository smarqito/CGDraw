#include "DirectionalLight.h"

/*
* 
f the w component of the position is 0,
the light is treated as a directional source. 
Diffuse and specular lighting calculations take the light's direction,
but not its actual position, into account, and attenuation is disabled.
https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glLight.xml
*/

DirectionalLight::DirectionalLight(int no, XMLElement* xmlElem) : Light(no)
{
	_point[0] = xmlElem->FloatAttribute("dirX");
	_point[1] = xmlElem->FloatAttribute("dirY");
	_point[2] = xmlElem->FloatAttribute("dirZ");
	_point[3] = 0.f;
}

void DirectionalLight::_draw()
{
	glLightfv(getLightNo(), GL_POSITION, _point);
}
