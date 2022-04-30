#ifndef MATRIX_H

#pragma once
#include <stdlib.h>
#include <cstdlib>

enum DefMat
{
	CATMULL,
	BEZIER,
	HERMITE
};

class Matrix
{
protected:
	float* _mat;
	int _m;
	int _n;
public:
	/*
	Default is Bezier
	*/
	Matrix();
	Matrix(int m, int n);
	Matrix(DefMat type);
	Matrix(int m, int n, float* values);
	/*
	Multiply THIS._mat by b
	result in Matrix out
	out = this._mat x b
	@param	b		Matrix to multiply
	@param	out		Resulting matrix;
					expected to be properly instantiated
	*/
	bool mul_matrix(Matrix b, Matrix out);
	/*
	Multiply this.*/
	Matrix mul_matrix(Matrix b);

	/*
	Set new value for point at line m, column n
	@param m		lineno
	@param n		columnno
	@param newValue	...
	*/
	void setPoint(int m, int n, float newValue);
	/*

	*/
	void setPoint(int absolute_index, float newValue);
	/*
	Get point line m, column n
	*/
	float getPoint(int m, int n);
	/*
	Get point at absolute index from 0 + abs_index
	*/
	float getPoint(int absolute_index);
	/*
	Transpose the matrix...
	*/
	void transpose();
	void cross(Matrix b, Matrix out);
	/*
	Normalize Matrix considering each line as a vector 
	*/
	void normalize_lines();
	float* to_array();
	int getM();
	int getN();
	Matrix clone();
};

#endif // !MATRIX_H