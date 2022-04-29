#include "Matrix.h"
// default matrix definition

static float CATMULL_MAT[16] = { -0.5f,  1.5f, -1.5f,  0.5f,
							1.0f, -2.5f,  2.0f, -0.5f,
							-0.5f,  0.0f,  0.5f,  0.0f,
							0.0f,  1.0f,  0.0f,  0.0f
};

static float BEZIER_MAT[16] = { -1.f, 3.f, -3.f, 1.f,
								3.f, -6.f, 3.f, 0.f,
								-3.f, 3.f, 0.f, 0.f,
								1.f, 0.f, 0.f, 0.f
};
static float HERMITE_MAT[16] = { 2.f, -2.f, 1.f, 1.f,
								-3.f, 3.f, -2.f,-1.f,
								0.f, 0.f, 0.f, 1.f,
								1.f, 0.f, 0.f, 0.f
};

Matrix::Matrix() : Matrix(CATMULL)
{
}

Matrix::Matrix(int m, int n)
{
	_mat = new float[m * n]();
	_m = m;
	_n = n;
}

Matrix::Matrix(DefMat type) : Matrix(4, 4)
{
	float* fill;
	switch (type)
	{
	case CATMULL:
		fill = CATMULL_MAT;
		break;
	case BEZIER:
		fill = BEZIER_MAT;
		break;
	case HERMITE:
		fill = HERMITE_MAT;
		break;
	default:
		break;
	}
	for (int i = 0; i < 16; i++)
	{
		_mat[i] = fill[i];
	}
}

bool Matrix::mul_matrix(Matrix b, Matrix out)
{
	if (_n != b._m) {
		return false;
	}
	float res[16];
	for (int i = 0; i < _m; i++)
	{
		for (int j = 0; j < b._n; j++) {
			out._mat[i * b._n + j] = 0;
			res[i * b._n + j] = 0;
			for (int k = 0; k < _n; k++)
			{
				out._mat[i * b._n + j] += _mat[i * _n + k] * b._mat[k * b._n + j];
				res[i * b._n + j] += _mat[i * _n + k] * b._mat[k * b._n + j];
			}
		}
	}
	return true;
}

Matrix Matrix::mul_matrix(Matrix b)
{
	Matrix res(_m, b._n);
	mul_matrix(b, res);
	return res;
}

void Matrix::setPoint(int m, int n, float newValue)
{
	setPoint(m * _n + n, newValue);
}

void Matrix::setPoint(int absolute_index, float newValue)
{
	_mat[absolute_index] = newValue;
}

float Matrix::getPoint(int m, int n)
{ 
	return getPoint(m * _n + n);
}

float Matrix::getPoint(int absolute_index)
{
	return _mat[absolute_index];
}
