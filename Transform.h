#pragma once
#include "cartesian.h"
#include <tinyxml2.h>

using namespace tinyxml2;

class Transform
{
private:
	XMLElement* _transform_elem;
	point _translate;
	point _scale;
	point _rotate_p;
	float _rotate_a;
	bool _t, _r, _s;
public:
	Transform(XMLElement* transform_elem);
	void _init();
	void _draw();
};
