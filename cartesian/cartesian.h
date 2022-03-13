#pragma once
#include <stdlib.h>
#include <list>

/*
* Estrutura de dados para classificar um ponto cartesiano
* Pontos do eixo 3D, x, y e z
*/
struct point {
	double x, y, z;
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
	point* points;
	int pos;
	int total;
	int _size;
public:
	t_points(int size) {
		pos = 0;
		total = 0;
		points = new point[size];
		_size = size;
	}
	int size() {
		return _size;
	}
	bool add_point(double x, double y, double z);
	bool add_point(point p);
	point get_point();
	point get_point(int pos);
	void _draw();
};

/*
* Criar um ponto a partir de coordenadas polares
*/
point polartocart(float r, float alpha, float beta);
