
/*
* Author: Group
* UC : Computacao Grafica
*/
#define _USE_MATH_DEFINES
#include <math.h>
#include "cartesian.h"

//t_points::t_points(int size) {
//	pos = 0;
//	total = 0;
//	this->size = size;
//	points = (point*)malloc(sizeof(point) * size);
//}

t_points::t_points()
{
	_pos = 0;
	_total = 0;
	_points = new point[10];
	_size = 10;
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
	point* p = (&_points[_total++]);
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

point polartocart(polar p) {
	return polartocart(p.r, p.a, p.b);
}

point polartocart(float r, float alpha, float beta) {
	point point;
	point.x = r * cos(beta) * sin(alpha);
	point.y = r * sin(beta);
	point.z = r * cos(beta) * cos(alpha);

	return point;
}

polar cart_to_polar(point p)
{
	return cart_to_polar(p.x, p.y, p.z);
}

polar cart_to_polar(double x, double y, double z)
{
	polar p;
	if (x == 0 || (x == 0 && y == 0 && z == 0)) {
		p.r = 1;
		p.a = 0;
		p.b = 0;
		return p;
	}
	p.r = sqrt(x * x + y * y + z * z);
	double raiz = sqrt(x * x + y * y);
	double cos2 = z / raiz;
	p.a = cos2 <= -1.0 ? M_PI : cos2 >= 1.0 ? 0 : -acos(cos2);
	p.b = asin(y / p.r);
	return p;
}

point sum_points(point a, point b)
{
	point p;
	p.x = a.x + b.x;
	p.y = a.y + b.y;
	p.z = a.z + b.z;
	return p;
}

void sum_points(point* a, point* b)
{
	a->x = a->x + b->x;
	a->y = a->y + b->y;
	a->z = a->z + b->z;
}

point sub_points(point a, point b)
{
	point p;
	p.x = a.x - b.x;
	p.y = a.y - b.y;
	p.z = a.z - b.z;
	return p;

}

point scale_factor(point x, float factor) {
	point p;
	p.x = x.x * factor;
	p.y = x.y * factor;
	p.z = x.z * factor;
	return p;

}

void sub_points(point* a, point* b)
{
	a->x = a->x - b->x;
	a->y = a->y - b->y;
	a->z = a->z - b->z;

}

bool mul_matrix(matrix* a, matrix* b, matrix* out)
{
	if (!a || !b || a->n != b->m) {
		return false;
	}
	out->m = a->m;
	out->n = b->n;
	for (int i = 0; i < a->m; i++)
	{
		for (int j = 0; j < b->n; j++) {
			out->mat[i * b->n + j] = 0;
			for (int k = 0; k < a->n; k++)
			{
				out->mat[i * b->n + j] += a->mat[i * a->n + k] * b->mat[k * b->n + j];
			}
		}
	}
	return true;
}

bool mul_matrix(pmatrix* a, matrix* b, pmatrix* out)
{
	if (!a || !b || a->n != b->m) {
		return false;
	}
	out->m = a->m;
	out->n = b->n;
	float tmp;
	for (int i = 0; i < a->m; i++)
	{
		for (int j = 0; j < b->n; j++) {
			out->mat[i * b->n + j].x = 0;
			out->mat[i * b->n + j].y = 0;
			out->mat[i * b->n + j].z = 0;
			for (int k = 0; k < a->n; k++)
			{
				tmp = b->mat[k * b->n + j];
				out->mat[i * b->n + j].x += a->mat[i * a->n + k].x * tmp;
				out->mat[i * b->n + j].y += a->mat[i * a->n + k].x * tmp;
				out->mat[i * b->n + j].z += a->mat[i * a->n + k].x * tmp;
			}
		}
	}
	return true;
}

bool mul_matrix(matrix* a, pmatrix* b, pmatrix* out)
{
	if (!a || !b || a->n != b->m) {
		return false;
	}
	out->m = a->m;
	out->n = b->n;
	float tmp;
	for (int i = 0; i < a->m; i++)
	{
		for (int j = 0; j < b->n; j++) {
			out->mat[i * b->n + j].x = 0;
			out->mat[i * b->n + j].y = 0;
			out->mat[i * b->n + j].z = 0;
			for (int k = 0; k < a->n; k++)
			{
				tmp = a->mat[i * a->n + k];
				out->mat[i * b->n + j].x += tmp * b->mat[k * b->n + j].x;
				out->mat[i * b->n + j].y += tmp * b->mat[k * b->n + j].y;
				out->mat[i * b->n + j].z += tmp * b->mat[k * b->n + j].z;
			}
		}
	}
	return true;
}

matrix mul_matrix(matrix a, matrix b)
{
	if (a.n != b.m) {
		throw "Matrix dim can't be multiplied";
	}
	float* tmp_ = (float*) malloc(sizeof(float) * a.m * b.n);
	//float tmp[m_i * b.n];
	matrix tmp_mat = { tmp_, a.m, b.n };
	mul_matrix(&a, &b, &tmp_mat);
	return tmp_mat;
}



void cross(point* a, point* b, point* res)
{
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
}

void normalize(point* a)
{
	float l = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	a->x /= l;
	a->y /= l;
	a->z /= l;
}

