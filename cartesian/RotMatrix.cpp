#include "RotMatrix.h"

RotMatrix::RotMatrix(Matrix x, Matrix y, Matrix z):Matrix(4,4)
{
	setPoint(0, x.getPoint(0)); setPoint(1, x.getPoint(1)); setPoint(2, x.getPoint(2)); setPoint(3, 0);
	setPoint(4, y.getPoint(0)); setPoint(5, y.getPoint(1)); setPoint(6, y.getPoint(2)); setPoint(7, 0);
	setPoint(8, z.getPoint(0)); setPoint(9, z.getPoint(1)); setPoint(10, z.getPoint(2)); setPoint(11, 0);
	setPoint(12, 0); setPoint(13,0); setPoint(14, 0); setPoint(15, 1);
}
