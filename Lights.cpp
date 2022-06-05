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
	float amb[4] = {1.f, 1.f, 1.f, 1.0f};
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	GLfloat dark[4] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
	float black[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	XMLElement* light = _xml_elem->FirstChildElement("light");
	int lightno = 0x0000;
	const char* type;
	while (lightno < GL_MAX_LIGHTS && light != NULL) {

		type = light->FindAttribute("type")->Value();
		glEnable(lightno + GL_LIGHT0);

		glLightfv(lightno + GL_LIGHT0, GL_AMBIENT, dark);
		glLightfv(lightno + GL_LIGHT0, GL_DIFFUSE, white);
		glLightfv(lightno + GL_LIGHT0, GL_SPECULAR, white);

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
