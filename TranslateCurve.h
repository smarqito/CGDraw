#pragma once
#include <vector>
#include "Curve.h"
#include "TimeControl.h"
#include "RotMatrix.h"

class TranslateCurve
{
	Curve _curve;
	Matrix _pos = Matrix(1, 3);
	Matrix _deriv = Matrix(1, 3);
	Matrix _x = _deriv;
	Matrix _y = Matrix(1, 3);
	Matrix _z = Matrix(1, 3);
	RotMatrix _rot_matrix;
	bool _align;
	void _draw_curve();
public:
	TranslateCurve();
	TranslateCurve(DefMat type);
	TranslateCurve(Matrix m);
	void addControlPoint(std::vector<Point> newPoints);
	void setAlign(bool align);
	void _draw(float time);

};
