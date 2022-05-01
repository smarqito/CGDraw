#pragma once

#include "Matrix.h"
class RotMatrix: public Matrix
{
public:
	RotMatrix();
	RotMatrix(Matrix x, Matrix y, Matrix z);
	void setX(Matrix x);
	void setY(Matrix y);
	void setZ(Matrix z);
	void setXYZ(Matrix x, Matrix y, Matrix z);
};
