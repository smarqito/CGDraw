#pragma once
#include <stdlib.h>
#include <list>
#ifndef CARTESIAN_H
/*
* Estrutura de dados para classificar um ponto cartesiano
* Pontos do eixo 3D, x, y e z
*/
struct matrix {
	float* mat;
	int m;
	int n;
};

class point {
public:
	float x, y, z;
	point() {
		x = 0;
		y = 0;
		z = 0;
	}
	point(float x_, float y_, float z_) {
		x = x_;
		y = y_;
		z = z_;
	};
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
	point* _points;
	int _pos;
	int _total;
	int _size;
public:
	t_points();
	t_points(int size);
	int size();
	int total();
	bool add_point(double x, double y, double z);
	bool add_point(point p);
	point get_point();
	point get_point(int pos);
	void _draw();
	point* get_points_ptr();
};

/*
* Criar um ponto a partir de coordenadas polares
*/
point polartocart(float r, float alpha, float beta);
point polartocart(polar p);

polar cart_to_polar(point p);

polar cart_to_polar(double x, double y, double z);

point sum_points(point a, point b);

void sum_points(point* a, point* b);

point sub_points(point a, point b);

void sub_points(point* a, point* b);

/*
* Multiply a vector by a factor f (x,y,z) = (fx, fy, fz)
*/
point scale_factor(point x, float factor);

/*
Equivalente a Out = AxB
@param a matriz A
@param b matriz B
@param out Apontador para matriz resultado
@return True if possible to multiply; False otherwise
*/
bool mul_matrix(matrix* a, matrix* b, matrix* out);

matrix mul_matrix(matrix a, matrix b);

/*
Cross-product between a x b
*/
void cross(point* a, point* b, point* res);

/*
Normaliza o ponto a
*/
void normalize(point* a);

#endif // !CARTESIAN_H