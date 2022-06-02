#pragma once
#include "Curve.h"
#include "PointMatrix.h"

class BezierTriangles
{
private:
	PointMatrix _points;	// 4 x 4
	PointMatrix _const;		// 4 x 4 :: M . P . M^T
	PointMatrix _u_mpm;		// 1 x 4 :: u . const
	PointMatrix _mpm_v;		// 1 x 1 :: .. v
	Matrix _m;				// 4 x 4
	Matrix _m_t;			// 4 x 4
	Matrix _u;				// 1 x 4
	Matrix _v;				// 4 x 1
	void calculateU(float u);
	void calculateV(float v);
public:
	/*
	Instantiate P matrix with m x n size
	@param m Number of rows
	@param n Number of columns
	*/
	BezierTriangles(int m, int n, Matrix transf);
	/*
	Do the precalculus of the matrices:
	_const = M x P x M^T
	*/
	void preCalculus();
	void setPatchPoint(int pos, float x, float y, float z);
	void setPatchPoint(int pos, float* v);
	void setPatchPoint(int pos, Point p);
	void setPatchPoint(int pos, std::vector<Point> points);
	Point getControlPoint(float u, float v);
	
};