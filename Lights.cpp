#include "Lights.h"

Lights::Lights()
{
}

Lights::Lights(XMLElement* xml)
{
	_xml_elem = xml; // must point to <lights> ... </lights>
	init();
}

void Lights::init()
{
	glEnable(GL_LIGHTING);
	XMLElement* light = _xml_elem->FirstChildElement("light");
	int lightno = GL_LIGHT0;
	const char* type;
	while (lightno < GL_MAX_LIGHTS && light != NULL) {
		type = light->FindAttribute("type")->Value();
		glEnable(lightno);

		if (strcmp(type, "point") == 0) {
			_lights.push_back(PointLight(lightno, light));

		}
		else if (strcmp(type, "directional") == 0)
		{
			_lights.push_back(DirectionalLight(lightno, light));
		}
		else if (strcmp(type, "spotlight") == 0)
		{
			_lights.push_back(Spotlight(lightno, light));
		}

		light = light->NextSiblingElement("light");
		lightno++;
	}

}

void Lights::_draw()
{
	for (unsigned int i = 0; i < _lights.size(); i++)
	{
		_lights[i]._draw();
	}
}
