#include <vector>
#include <math.h>

#include "cartesian.h"
#ifndef CURVE_H


#pragma once
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
	matrix _m; // 4x4 : catmull, bezier, ...
	std::vector<point> _control_points;
	matrix _tmp;
	float *_pos_t_ptr; //size 4
	matrix _pos_t;
	float *_pos_d_ptr; //size 4
	matrix _pos_d;
	void calculate_t(float t);
	void calculate(float t, matrix* pos, matrix* deriv);
public:
	/*
	Default is Catmull Curve
	*/
	Curve();
	/*
	Can be used a modified curve definition
	@param curve_def 4x4 matrix
	*/
	Curve(float* curve_def); // must get 4x4 matrix
	void addControlPoint(float x, float y, float z);
	void addControlPoint(float* v);
	void addControlPoint(point p);
	void addControlPoint(std::vector<point> points);
	/*
	Calculate the point using gt segment
	@param gt
	@param pos 1x3 matrix
	@param deriv 1x3 matrix
	*/
	void getPoint(float gt, std::vector<int> control_index, matrix* pos, matrix* deriv);
};

#endif // !CURVE_H