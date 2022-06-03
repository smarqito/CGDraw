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
	float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	XMLElement* light = _xml_elem->FirstChildElement("light");
	int lightno = 0x0000;
	const char* type;
	while (lightno < GL_MAX_LIGHTS && light != NULL) {

		type = light->FindAttribute("type")->Value();
		glEnable(lightno + GL_LIGHT0);

		if (strcmp(type, "point") == 0) {
			_lights.push_back(new PointLight(lightno + GL_LIGHT0, light));
		}
		else if (strcmp(type, "directional") == 0)
		{
			_lights.push_back(new DirectionalLight(lightno + GL_LIGHT0, light));
		}
		else if (strcmp(type, "spotlight") == 0)
		{
			_lights.push_back(new Spotlight(lightno + GL_LIGHT0, light));
		}

		light = light->NextSiblingElement("light");
		lightno++;
	}

}

void Lights::_draw()
{
	for (unsigned int i = 0; i < _lights.size(); i++)
	{
		Light* l = _lights[i];
		l->_draw();
	}
}
