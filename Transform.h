#pragma once
#include <GL/glut.h>
#include "cartesian.h"
#include <tinyxml2.h>
#include <vector>

using namespace std;
using namespace tinyxml2;

enum type
{
	TRANSLATE,
	ROTATE,
	SCALE
};

struct transformation {
	Point p; // transformation x, y, z
	float a; // angle (use in rotate)
	type t; // type: translate, rotate, scale
};

class Transform
{
private:
	XMLElement* _transform_elem;
	vector<transformation> _transformations;
public:
	Transform();
	Transform(XMLElement* transform_elem);
	void _init();
	void _draw();
};
