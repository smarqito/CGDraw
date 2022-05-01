#pragma once
#include <stdlib.h>
#include <list>
#ifndef CARTESIAN_H
#include "Point.h"
/*
* Estrutura de dados para classificar um ponto cartesiano
* Pontos do eixo 3D, x, y e z
*/
struct matrix {
	float* mat;
	int m;
	int n;
};


struct pmatrix {
	Point* mat;
	int m;
	int n;
};

struct polar {
	float r, a, b;
};

struct perspective {
	float fov, nr, fr;
};

/*
* Estrutura de dados dos pontos para construir uma figura geométrica
* Os pontos são tuplos -> coordenadas cartesianas x y z
* Os membros são:
*	points -> Array de pontos
*	size   -> Número de pontos
*	pos    -> Posição atual no array
*	total  -> total de elementos que existem até ao momento
*/
class t_points {
	Point* _points;
	int _pos;
	int _total;
	int _size;
public:
	t_points();
	t_points(int size);
	int size();
	int total();
	bool add_point(double x, double y, double z);
	bool add_point(Point p);
	Point get_point();
	Point get_point(int pos);
	void _draw();
	Point* get_points_ptr();
};

/*
* Criar um ponto a partir de coordenadas polares
*/
Point polartocart(float r, float alpha, float beta);
Point polartocart(polar p);

polar cart_to_polar(Point p);

polar cart_to_polar(double x, double y, double z);

Point sum_points(Point a, Point b);

void sum_points(Point* a, Point* b);

Point sub_points(Point a, Point b);

void sub_points(Point* a, Point* b);

/*
* Multiply a vector by a factor f (x,y,z) = (fx, fy, fz)
*/
Point scale_factor(Point x, float factor);

/*
Equivalente a Out = AxB
@param a matriz A
@param b matriz B
@param out Apontador para matriz resultado
@return True if possible to multiply; False otherwise
*/
bool mul_matrix(matrix* a, matrix* b, matrix* out);
/*
*/
bool mul_matrix(pmatrix* a, matrix* b, pmatrix* out);
bool mul_matrix(matrix* a, pmatrix* b, pmatrix* out);

matrix mul_matrix(matrix a, matrix b);

/*
Cross-product between a x b
*/
void cross(Point* a, Point* b, Point* res);

/*
Normaliza o ponto a
*/
void normalize(Point* a);

/*
Transpose matrix
*/
void transpose(matrix* a, matrix* res);

#endif // !CARTESIAN_H