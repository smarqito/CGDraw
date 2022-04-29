#pragma once
#include "cartesian.h"
#include "Matrix.h"


class PointMatrix
{
	Point* _mat;
	int _m;
	int _n;
public:
	PointMatrix();
	PointMatrix(int m, int n);
	bool mul_matrix(PointMatrix b, PointMatrix out);
	/*
	out = this x b
	*/
	bool mul_matrix(Matrix b, PointMatrix out);
	/*
	out = b x this
	*/
	bool mul_matrix(PointMatrix out, Matrix b);
	/*
	Multiply this.*/
	PointMatrix mul_matrix(PointMatrix b);
	/*
	Set new value for point at line m, column n
	@param m		lineno
	@param n		columnno
	@param newValue	...
	*/
	void setPoint(int m, int n, Point p);
	/*
	*/
	void setPoint(int absolute_index, Point p);
	/*
	*/
	void setPoint(int m, int n, float x, float y, float z);
	/*
	*/
	void setPoint(int absolute_index, float x, float y, float z);
	/*
	Get point line m, column n
	*/
	Point getPoint(int m, int n);
	/*
	Get point at absolute index from 0 + abs_index
	*/
	Point getPoint(int absolute_index);
	/*
	Transpose the matrix...
	*/
	void transpose();

};
