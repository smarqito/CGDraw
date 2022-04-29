#pragma once
#include <GL/glut.h>
#include "cartesian.h"
#include <tinyxml2.h>
#include <vector>
#include <math.h>
#include "curves/curves.h"

using namespace std;
using namespace tinyxml2;

enum type
{
	TRANSLATE,
	ROTATE,
	SCALE
};

struct transformation {
	point p; // transformation x, y, z
	vector<point> points; // points to define a Catmull-Rom cubic curve
	float time; //the number of seconds to run the whole curve
	bool align; //aligned with the curve
	float a; // angle (use in rotate)
	type t; // type: translate, rotate, scale
	bool curve; // if the transformation use cubic curve
	float last_time;
	float translate_rate;
	float rotate_rate;
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
