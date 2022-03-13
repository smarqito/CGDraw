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

bool t_points::add_point(double x, double y, double z) {
	if (total == size()) {
		return false;
	}
	point *p = (& points[total++]);
	p->x = x;
	p->y = y;
	p->z = z;
	return true;
}

bool t_points::add_point(point p) {
	return add_point(p.x, p.y, p.z);
}

point t_points::get_point() {
	return get_point(this->pos++);
}

point t_points::get_point(int pos) {
	if (pos < total) {
		return points[pos];
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

void t_points::_draw() {
	point p;
	for (int i = 0; i < this->size(); i++) {
		p = get_point(i);
		//glVertex3d(p.x, p.y, p.z);
	}
}