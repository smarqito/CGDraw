#include "RotMatrix.h"
#include "RotMatrix.h"
#include "RotMatrix.h"
#include "RotMatrix.h"
#include "RotMatrix.h"
#include "RotMatrix.h"

RotMatrix::RotMatrix() : Matrix(4,4)
{
	setPoint(15, 1);
}

RotMatrix::RotMatrix(Matrix x, Matrix y, Matrix z): RotMatrix()
{
	setPoint(0, x.getPoint(0)); setPoint(1, x.getPoint(1)); setPoint(2, x.getPoint(2));
	setPoint(4, y.getPoint(0)); setPoint(5, y.getPoint(1)); setPoint(6, y.getPoint(2));
	setPoint(8, z.getPoint(0)); setPoint(9, z.getPoint(1)); setPoint(10, z.getPoint(2));
}

void RotMatrix::setX(Matrix x)
{
	setPoint(0, x.getPoint(0)); setPoint(1, x.getPoint(1)); setPoint(2, x.getPoint(2));
}

void RotMatrix::setY(Matrix y)
{
	setPoint(4, y.getPoint(0)); setPoint(5, y.getPoint(1)); setPoint(6, y.getPoint(2));
}

void RotMatrix::setZ(Matrix z)
{
	setPoint(8, z.getPoint(0)); setPoint(9, z.getPoint(1)); setPoint(10, z.getPoint(2));
}

void RotMatrix::setXYZ(Matrix x, Matrix y, Matrix z)
{
	setX(x);
	setY(y);
	setZ(z);
}
