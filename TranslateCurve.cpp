#include "TranslateCurve.h"


TranslateCurve::TranslateCurve() : TranslateCurve(CATMULL)
{
}

TranslateCurve::TranslateCurve(Matrix m)
{
	_curve = Curve(m);
	_y.setPoint(1, 1);
}

TranslateCurve::TranslateCurve(DefMat type)
{
	_curve = Curve(type);
	_y.setPoint(1, 1);
}

void TranslateCurve::addControlPoint(std::vector<Point> newPoints)
{
	_curve.addControlPoint(newPoints);
}

void TranslateCurve::setAlign(bool align)
{
	_align = align;
}

void TranslateCurve::_draw_curve()
{
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 1; i+=0.01)
	{
		_curve.getPoint(i, _pos, _deriv);
		glVertex3d(_pos.getPoint(0), _pos.getPoint(1), _pos.getPoint(2));
	}
	glEnd();	
	glBegin(GL_LINES);
	for (float i = 0; i < 1; i += 0.01)
	{
		_curve.getPoint(i, _pos, _deriv);
		glVertex3f(_pos.getPoint(0), _pos.getPoint(1), _pos.getPoint(2));
		glVertex3f(_pos.getPoint(0) + _deriv.getPoint(0), _pos.getPoint(1) + _deriv.getPoint(1), _pos.getPoint(2) + _deriv.getPoint(2));
	}
	glEnd();

}

void TranslateCurve::_draw(float time)
{
	//_draw_curve();
	_curve.getPoint(time, _pos, _deriv);
	glTranslatef(_pos.getPoint(0), _pos.getPoint(1), _pos.getPoint(2));
	if (_align) {
		_deriv.cross(_y, _z);
		_z.cross(_deriv, _y);

		_deriv.normalize_lines();
		_y.normalize_lines();
		_z.normalize_lines();
		_rot_matrix.setXYZ(_x, _y, _z);

		glMultMatrixf(_rot_matrix.to_array());
	}
}