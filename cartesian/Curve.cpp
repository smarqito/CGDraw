#include "Curve.h"

void Curve::calculate_t(float t) {
	// calculate pos
	_pos_t_ptr[0] = t * t * t;
	_pos_t_ptr[1] = t * t;
	_pos_t_ptr[2] = t;
	_pos_t_ptr[3] = 1;
	// calculate derivative
	_pos_d_ptr[0] = 3 * t * t;
	_pos_d_ptr[1] = 2 * t;
	_pos_d_ptr[2] = 1;
	_pos_d_ptr[3] = 0;
}

void Curve::calculate(float t, matrix* pos, matrix* deriv)
{
	matrix a = mul_matrix(_m, _tmp);
	calculate_t(t); // will modify _pos_#_ptr (both)
	mul_matrix(&_pos_t, &a, pos);
	mul_matrix(&_pos_d, &a, deriv);
}


Curve::Curve()
{
	_m.mat = catmull;
	_m.m = 4;
	_m.n = 4;

	_tmp.mat = (float*)malloc(sizeof(float) * 4 * 3);
	_tmp.m = 4;
	_tmp.n = 3;
}

Curve::Curve(float* curve_def)
{
	_m.mat = curve_def;
	_m.m = 4;
	_m.n = 4;

	_tmp.mat = (float*)malloc(sizeof(float) * 4 * 3);
	_tmp.m = 4;
	_tmp.n = 3;
}

void Curve::addControlPoint(float x, float y, float z)
{
	point p = {
		x, y, z
	};
	addControlPoint(p);
}

void Curve::addControlPoint(float* v)
{
	point p = {
		v[0], v[1], v[2]
	};
	addControlPoint(p);
}

void Curve::addControlPoint(point p)
{
	_control_points.push_back(p);
}

void Curve::getPoint(float gt, matrix* pos, matrix* deriv)
{
	int size = _control_points.size();
	float t = gt * size; // real global t
	int index = floor(t); // which segment
	t = t - index; // where within segment

	int i[4];
	i[0] = (index + size - 1) % size;
	i[1] = (i[0] + 1) % size;
	i[2] = (i[1] + 1) % size;
	i[3] = (i[2] + 1) % size;

	// populate _tmp matrix with current 4 control points
	for (int j = 0; j < 4; j++)
	{
		_tmp.mat[3 * j] = _control_points[j].x;
		_tmp.mat[3 * j + 1] = _control_points[j].y;
		_tmp.mat[3 * j + 2] = _control_points[j].y;
	}
	calculate(t, pos, deriv);
}
