#pragma once
#include <GL/glut.h>
#include "cartesian.h"
#include <tinyxml2.h>
#include <vector>
#include <Curve.h>
#include <RotMatrix.h>
#include "TranslateCurve.h"

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
	vector<Point> points;
	float time; //the number of seconds to run the whole curve
	bool align; //aligned with the curve
	float a; // angle (use in rotate)
	type t; // type: translate, rotate, scale
	bool curve = false; // if the transformation use cubic curve
	TranslateCurve _t_curve; // points to define a Catmull-Rom cubic curve
	TimeControl _time;
	float last_time;
	float translate_rate;
	float rotate_rate;
};

class Transform
{
private:
	XMLElement* _transform_elem;
	vector<transformation> _transformations;
	Matrix _y_i = Matrix(1,3);
	Matrix _custom_matrix(XMLElement* matrix);
public:
	Transform();
	Transform(XMLElement* transform_elem);
	void _init();
	void _draw();
};
