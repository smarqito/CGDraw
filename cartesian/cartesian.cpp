#include "cartesian.h"
#include "cartesian.h"
#include "cartesian.h"

/*
* Author: Group
* UC : Computacao Grafica
*/
#include "cartesian.h"
#include <math.h>
//#include <GL/glut.h>

//t_points::t_points(int size) {
//	pos = 0;
//	total = 0;
//	this->size = size;
//	points = (point*)malloc(sizeof(point) * size);
//}

t_points::t_points()
{
}

t_points::t_points(int size) {
	_pos = 0;
	_total = 0;
	_points = new point[size];
	_size = size;
}

int t_points::size()
{
	return _size;
}

int t_points::total()
{
	return _total;
}

bool t_points::add_point(double x, double y, double z) {
	if (_total == size()) {
		return false;
	}
	point *p = (& _points[_total++]);
	p->x = x;
	p->y = y;
	p->z = z;
	return true;
}

bool t_points::add_point(point p) {
	return add_point(p.x, p.y, p.z);
}

point t_points::get_point() {
	return get_point(this->_pos++);
}

point t_points::get_point(int pos) {
	if (pos < _total) {
		return _points[pos];
	}
	throw 0x1;
}

point polartocart(float r, float alpha, float beta) {
	point point;
	point.x = r * cos(beta) * sin(alpha);
	point.y = r * sin(beta);
	point.z = r * cos(beta) * cos(alpha);

	return point;
}

point cart_to_polar(double x, double y, double z) {
	point p;
	p.x = sqrt(x * x + y * y + z * z); // radius
	p.y = asin(y / p.x);
	p.z = asin(x / sqrt(x * x + y * y)) * (y < 0 ? -1 : 1); 
	return p;
}

void t_points::_draw() {
	point p;
	for (int i = 0; i < this->size(); i++) {
		p = get_point(i);
		//glVertex3d(p.x, p.y, p.z);
	}
}

point* t_points::get_points_ptr()
{
	return _points;
}

