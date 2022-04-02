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
	point p;
	float a;
	type t;
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
