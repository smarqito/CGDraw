#pragma once
#include "Curve.h"

class BezierTriangles: public Curve
{
private:
	matrix _m;
	matrix _m_t;
	pmatrix _p;
	/*
	Instantiate P matrix with m x n size
	@param m Number of rows
	@param n Number of columns
	*/
	BezierTriangles(int m, int n);
	
};