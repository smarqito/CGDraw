#include "PointMatrix.h"
#include <iostream>

PointMatrix::PointMatrix()
{
}

PointMatrix::PointMatrix(int m, int n)
{
	_m = m;
	_n = n;
	_mat = new Point[m * n];
}

bool PointMatrix::mul_matrix(PointMatrix b, PointMatrix out)
{
	throw "Nao implementado";
}

bool PointMatrix::mul_matrix(Matrix b, PointMatrix out)
{
	if (_n != b.getM()) {
		return false;
	}
	out._m = _m;
	out._n = b.getN();
	Point tmp;
	for (int i = 0; i < _m; i++)
	{
		for (int j = 0; j < out._n; j++) {
			out._mat[i * out._n + j].x = 0;
			out._mat[i * out._n + j].y = 0;
			out._mat[i * out._n + j].z = 0;
			for (int k = 0; k < _n; k++)
			{
				tmp = _mat[i * out._n + k];
				out._mat[i * out._n + j].x += tmp.x * b.getPoint(k * out._n + j);
				out._mat[i * out._n + j].y += tmp.y * b.getPoint(k * out._n + j);
				out._mat[i * out._n + j].z += tmp.z * b.getPoint(k * out._n + j);
			}
		}
	}
	return true;

}

bool PointMatrix::mul_matrix(PointMatrix out, Matrix a)
{
	out._m = a.getM();
	out._n = _n;
	float tmp;
	for (int i = 0; i < out._m; i++)
	{
		for (int j = 0; j < _n; j++) {
			out._mat[i * _n + j].x = 0;
			out._mat[i * _n + j].y = 0;
			out._mat[i * _n + j].z = 0;
			for (int k = 0; k < a.getN(); k++)
			{
				tmp = a.getPoint(i * a.getN() + k);
				out._mat[i * _n + j].x += tmp * _mat[k * _n + j].x;
				out._mat[i * _n + j].y += tmp * _mat[k * _n + j].y;
				out._mat[i * _n + j].z += tmp * _mat[k * _n + j].z;
			}
		}
	}
	return true;
}

PointMatrix PointMatrix::mul_matrix(PointMatrix b)
{
	PointMatrix res(_m, _n);
	mul_matrix(b, res);
	return res;
}

void PointMatrix::setPoint(int m, int n, Point p)
{
	setPoint(m * _n + n, p);
}

void PointMatrix::setPoint(int absolute_index, Point p)
{
	_mat[absolute_index].setPoint(p);
}

void PointMatrix::setPoint(int m, int n, float x, float y, float z)
{
	setPoint(m * _n + n, x, y, z);
}

void PointMatrix::setPoint(int absolute_index, float x, float y, float z)
{
	_mat[absolute_index].setPoint(x, y, z);
}

Point PointMatrix::getPoint(int m, int n)
{
	return getPoint(n * _n + n);
}

Point PointMatrix::getPoint(int absolute_index)
{
	return _mat[absolute_index];
}

void PointMatrix::transpose()
{
	Point* res = new Point[_m * _n];
	for (int i = 0; i < _n; i++)
	{
		for (int j = 0; j < _m; j++)
		{
			res[i * _m + j] = _mat[j * _n + i];
		}
	}

	int tmp = _m;
	_m = _n;
	_n = tmp;

	free(_mat);
	_mat = res;

}

PointMatrix PointMatrix::clone()
{
	PointMatrix res(_m, _n);
	int total = _m * _n;
	for (int i = 0; i < total; i++)
	{
		res._mat[i].setPoint(_mat[i]);
	}
	return res;
}
