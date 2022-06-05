#include "Spotlight.h"
#include <CGDraw.h>


Spotlight::Spotlight(int no, XMLElement* xmlElem) : Light(no)
{
	_dir[0] = xmlElem->FloatAttribute("dirx");
	_dir[1] = xmlElem->FloatAttribute("diry");
	_dir[2] = xmlElem->FloatAttribute("dirz");
	_dir[3] = 0.f;
	_point[0] = xmlElem->FloatAttribute("posx");
	_point[1] = xmlElem->FloatAttribute("posy");
	_point[2] = xmlElem->FloatAttribute("posz");
	_point[3] = 1.f;
	_cutoff = xmlElem->FloatAttribute("cutoff");
}

void Spotlight::_draw()
{
	glLightfv(getLightNo(), GL_POSITION, _point);
	glLightfv(getLightNo(), GL_SPOT_DIRECTION, _dir);
	glLightf(getLightNo(), GL_SPOT_CUTOFF, _cutoff);
}
