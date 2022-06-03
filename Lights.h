#pragma once

#ifndef LIGHTS_H
#define LIGHTS_H


#include <Light.h>
//#include <CGDraw.h>
#include "Spotlight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

#include <tinyxml2.h>
#include <vector>
#include <iostream>
#include <typeinfo>

using namespace tinyxml2;

class Lights
{
private:
	XMLElement* _xml_elem;
	std::vector<Light> _lights;
public:
	Lights();
	Lights(XMLElement* xml);
	void init();
	void _draw();
};

#endif // !LIGHTS_H