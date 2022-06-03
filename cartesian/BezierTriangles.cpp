#include "BezierTriangles.h"

void BezierTriangles::calculateU(float u)
{
	_u.setPoint(0, u * u * u);
	_u.setPoint(1, u * u);
	_u.setPoint(2, u);
	_u.setPoint(3, 1);
}

void BezierTriangles::calculateDerivativeU(float u)
{
	_u.setPoint(0, 3 * u * u);
	_u.setPoint(1, 2 * u);
	_u.setPoint(2, 1);
	_u.setPoint(3, 0);
}

void BezierTriangles::calculateV(float v)
{
	_v.setPoint(0, v * v * v);
	_v.setPoint(1, v * v);
	_v.setPoint(2, v);
	_v.setPoint(3, 1);
}

void BezierTriangles::calculateDerivativeV(float v)
{
	_v.setPoint(0, 3 * v * v);
	_v.setPoint(1, 2 * v);
	_v.setPoint(2, 1);
	_v.setPoint(3, 0);
}

BezierTriangles::BezierTriangles(int m, int n, Matrix transf)
{
	_m = transf.clone();
	_m_t = transf.clone();
	_m_t.transpose();
	_u = Matrix(1, 4);
	_v = Matrix(4, 1);
	_const = PointMatrix(m, n);
	_points = PointMatrix(m, n);
	_u_mpm = PointMatrix(1, 4);
	_mpm_v = PointMatrix(1, 1);
}

void BezierTriangles::preCalculus()
{
	// _const = M x P
	PointMatrix mp(4, 4);
	_points.mul_matrix(mp, _m);
	// _const = (MxP) x M^T
	mp.mul_matrix(_m_t, _const);
}

void BezierTriangles::setPatchPoint(int pos, float x, float y, float z)
{
	_points.setPoint(pos, x, y, z);
}

void BezierTriangles::setPatchPoint(int pos, float* v)
{
	setPatchPoint(pos, v[0], v[1], v[2]);
}

void BezierTriangles::setPatchPoint(int pos, Point p)
{
	_points.setPoint(pos, p);
}

void BezierTriangles::setPatchPoint(int pos, std::vector<Point> points)
{
	for (int i = 0; i < points.size(); i++)
	{
		setPatchPoint(pos + i, points[i]);
	}
}

Point BezierTriangles::getControlPoint(float u, float v)
{
	calculateU(u); // 1 x 4
	calculateV(v); // 4 x 1
	_const.mul_matrix(_u_mpm, _u); // (1 x 4) x (4 x 4)  = 1 x 4 = _u_mpm
	_u_mpm.mul_matrix(_v, _mpm_v); // (1 x 4) x (4 x 1)  = 1 x 1 = _mpm_v
	return _mpm_v.getPoint(0);

}

Point BezierTriangles::getNormal(float u, float v)
{
	calculateDerivativeU(u); // 1 x 4
	calculateV(v); // 4 x 1
	_const.mul_matrix(_u_mpm, _u); // (1 x 4) x (4 x 4)  = 1 x 4 = _u_mpm
	_u_mpm.mul_matrix(_v, _mpm_v); // (1 x 4) x (4 x 1)  = 1 x 1 = _mpm_v
	Point vector_u = _mpm_v.getPoint(0);

	calculateU(u); // 1 x 4
	calculateDerivativeV(v); // 4 x 1
	_const.mul_matrix(_u_mpm, _u); // (1 x 4) x (4 x 4)  = 1 x 4 = _u_mpm
	_u_mpm.mul_matrix(_v, _mpm_v); // (1 x 4) x (4 x 1)  = 1 x 1 = _mpm_v
	Point vector_v = _mpm_v.getPoint(0);

	Point n;
	cross(&vector_v, &vector_u, &n);
	normalize(&n);
	return n;

}
