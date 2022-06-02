#include "Curve.h"

void Curve::calculate_t(float t) {
	// calculate pos
	_pos_t.setPoint(0, t * t * t);
	_pos_t.setPoint(1, t * t);
	_pos_t.setPoint(2, t);
	_pos_t.setPoint(3, 1);
	// calculate derivative
	_pos_d.setPoint(0, 3 * t * t);
	_pos_d.setPoint(1, 2 * t);
	_pos_d.setPoint(2, 1);
	_pos_d.setPoint(3, 0);
}

Curve::Curve(Matrix m) : Curve()
{
	_m = m.clone();
}

void Curve::calculate(float t, Matrix pos, Matrix deriv)
{
	// a = _m x _tmp
	Matrix a = _m.mul_matrix(_tmp);
	//matrix a = mul_matrix(_m, _tmp);
	calculate_t(t); // will modify _pos_d & _pos_t matrix
	// pos = _pos_t x a
	_pos_t.mul_matrix(a, pos);
	//mul_matrix(&_pos_t, &a, pos);
	_pos_d.mul_matrix(a, deriv);
	//mul_matrix(&_pos_d, &a, deriv);
}


Curve::Curve()
{
	_pos_t = Matrix(1, 4);
	_pos_d = Matrix(1, 4);
	_tmp = Matrix(4, 3);
}

Curve::Curve(float* curve_def) : Curve()
{
	_m = Matrix(4, 4);
	// TODO accept external pointer as matrix
	//@@@@@ _m.mat = curve_def;
}

Curve::Curve(DefMat type) : Curve()
{
	_m = Matrix(type);
}

void Curve::addControlPoint(float x, float y, float z)
{
	Point p(x, y, z);
	addControlPoint(p);
}

void Curve::addControlPoint(float* v)
{
	Point p(v[0], v[1], v[2]);
	addControlPoint(p);
}

void Curve::addControlPoint(Point p)
{
	_control_points.push_back(p);
}

void Curve::addControlPoint(std::vector<Point> points)
{
	for (size_t i = 0; i < points.size(); i++)
	{
		_control_points.push_back(points[i]);
	}
}

void Curve::getPoint(float gt, Matrix pos, Matrix deriv)
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
		_tmp.setPoint(j, 0, _control_points[i[j]].x);
		_tmp.setPoint(j, 1, _control_points[i[j]].y);
		_tmp.setPoint(j, 2, _control_points[i[j]].z);
		//_tmp.mat[3 * j + 1] = _control_points[control_index[i[j]]].y;
		//_tmp.mat[3 * j + 2] = _control_points[control_index[i[j]]].z;
	}
	calculate(t, pos, deriv);
}