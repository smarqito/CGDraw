#pragma once
#include <vector>
#include <math.h>

#ifndef CURVE_H
#include "cartesian.h"
#include "Matrix.h"
using namespace std;

/*
Class that's able to generate curves based on
control points
Procedure:
1. add points
2. get point for each GT
2.1 pos and deriv must be 1x3 matrix*/
class Curve
{
private:
	Matrix _m; // 4x4 : catmull, bezier, ...
	vector<point> _control_points;
	// add new instance var for patches (???)
	// matrix application as constexpr
	Matrix _tmp;		// size 4 x 3
	Matrix _pos_t;		// size 1 x 4
	Matrix _pos_d;		// size 1 x 4
	void calculate_t(float t);
	void calculate(float t, Matrix pos, Matrix deriv);
public:
	/*
	Default is bezier
	*/
	Curve();
	/*
	Type of transformation matrix
	*/
	Curve(DefMat type);
	/*
	Can be used a modified curve definition
	@param curve_def 4x4 matrix
	*/
	Curve(float* curve_def); // must get 4x4 matrix
	void addControlPoint(float x, float y, float z);
	void addControlPoint(float* v);
	void addControlPoint(point p);
	void addControlPoint(vector<point> points);
	/*
	Calculate the point using gt segment
	@param gt
	@param pos 1x3 matrix
	@param deriv 1x3 matrix
	*/
	void getPoint(float gt, std::vector<int> control_index, Matrix pos, Matrix deriv);
};

#endif // !CURVE_H