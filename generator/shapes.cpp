#include "shapes.h"

// ---------------------------- Funções Auxiliares -------------------------------------
/*
* Criar um ponto a partir de coordenadas polares
*/
tuple<float, float, float> polartocart(float r, float alpha, float beta) {

	float x = r * cos(beta) * sin(alpha);
	float y = r * sin(beta);
	float z = r * cos(beta) * cos(alpha);

	return tuple<float, float, float>(x, y, z);
}

/*
* Função que adiciona um ponto ao array de pontos
*/
void add_point(tuple<float, float, float> point, t_points* all_points) {

	int pos = all_points->pos++;

	all_points->points[pos] = point;
}
// ------------------------------------------------------------------------------------

t_points* create_plane(float length, int divisions) {
	t_points* plane_points = (t_points*)malloc(sizeof(struct t_points));
	plane_points->pos = 0;

	plane_points->size = 6 * pow(divisions, 2);
	int size = plane_points->size;

	plane_points->points = (tuple<float, float, float>*) malloc(sizeof(tuple<float, float, float>) * size);

	float x = length / 2;
	float z = length / 2;
	float step = length / divisions;

	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {

			add_point(tuple<float, float, float>(x, 0, z), plane_points);
			add_point(tuple<float, float, float>(x, 0, z - step), plane_points);
			add_point(tuple<float, float, float>(x - step, 0, z), plane_points);

			add_point(tuple<float, float, float>(x - step, 0, z), plane_points);
			add_point(tuple<float, float, float>(x, 0, z - step), plane_points);
			add_point(tuple<float, float, float>(x - step, 0, z - step), plane_points);

			z -= step;
		}
		x -= step;
		z = length / 2; //volta ao valor inicial
	}

	return plane_points;
}


t_points* create_box(float units, int divisions) {
	t_points* box_points = (t_points*)malloc(sizeof(struct t_points));

	box_points->size = 3 * pow(divisions, 2) * 12;
	int size = box_points->size;

	box_points->points = (tuple<float, float, float>*) malloc(sizeof(tuple<float, float, float>) * size);

	float z = units / 2;
	float x = units / 2;

	float step = units / divisions;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {

			//face inferior
			add_point(tuple<float, float, float>(x, 0, z), box_points);
			add_point(tuple<float, float, float>(x - step, 0, z), box_points);
			add_point(tuple<float, float, float>(x, 0, z - step), box_points);

			add_point(tuple<float, float, float>(x - step, 0, z), box_points);
			add_point(tuple<float, float, float>(x - step, 0, z - step), box_points);
			add_point(tuple<float, float, float>(x, 0, z - step), box_points);

			//face superior

			add_point(tuple<float, float, float>(x, units, z), box_points);
			add_point(tuple<float, float, float>(x, units, z - step), box_points);
			add_point(tuple<float, float, float>(x - step, units, z), box_points);

			add_point(tuple<float, float, float>(x - step, units, z), box_points);
			add_point(tuple<float, float, float>(x, units, z - step), box_points);
			add_point(tuple<float, float, float>(x - step, units, z - step), box_points);

			z -= step;
		}
		x -= step;
		z = units / 2; //volta ao valor inicial
	}

	x = units / 2;
	float y = 0;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {

			//face lateral X positivo
			add_point(tuple<float, float, float>(x, y, z), box_points);
			add_point(tuple<float, float, float>(x, y, z - step), box_points);
			add_point(tuple<float, float, float>(x, y + step, z), box_points);

			add_point(tuple<float, float, float>(x, y + step, z), box_points);
			add_point(tuple<float, float, float>(x, y, z - step), box_points);
			add_point(tuple<float, float, float>(x, y + step, z - step), box_points);

			//face lateral X negativo
			add_point(tuple<float, float, float>(-x, y + step, z), box_points);
			add_point(tuple<float, float, float>(-x, y, z - step), box_points);
			add_point(tuple<float, float, float>(-x, y, z), box_points);

			add_point(tuple<float, float, float>(-x, y + step, z - step), box_points);
			add_point(tuple<float, float, float>(-x, y, z - step), box_points);
			add_point(tuple<float, float, float>(-x, y + step, z), box_points);

			y += step;
		}
		z -= step;
		y = 0; //volta ao valor inicial
	}
	z = units / 2;
	y = 0;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {
			//face lateral Y positivo
			add_point(tuple<float, float, float>(x, y, z), box_points);
			add_point(tuple<float, float, float>(x, y + step, z), box_points);
			add_point(tuple<float, float, float>(x - step, y, z), box_points);

			add_point(tuple<float, float, float>(x, y + step, z), box_points);
			add_point(tuple<float, float, float>(x - step, y + step, z), box_points);
			add_point(tuple<float, float, float>(x - step, y, z), box_points);

			//face lateral Y negativo
			add_point(tuple<float, float, float>(x, y, -z), box_points);
			add_point(tuple<float, float, float>(x - step, y, -z), box_points);
			add_point(tuple<float, float, float>(x, y + step, -z), box_points);

			add_point(tuple<float, float, float>(x, y + step, -z), box_points);
			add_point(tuple<float, float, float>(x - step, y, -z), box_points);
			add_point(tuple<float, float, float>(x - step, y + step, -z), box_points);
			y += step;
		}
		x -= step;
		y = 0; //volta ao valor inicial
	}

	return box_points;
}

t_points* create_sphere(int radius, int slices, int stacks) {
	t_points* sphere_points= (t_points*)malloc(sizeof(struct t_points));

	sphere_points->size = 6 * stacks * slices;
	int size = sphere_points->size;

	sphere_points->points = (tuple<float, float, float>*) malloc(sizeof(tuple<float, float, float>) * size);

	float sst = M_PI / stacks;
	float ssl = 2 * M_PI / slices;
	float beta = -M_PI / 2;
	float alpha = 0;

	for (int i = 0; i < stacks; i++)
	{
		for (int i = 0; i < slices; i++)
		{
			tuple<float, float, float> a = polartocart(radius, alpha, beta);
			tuple<float, float, float> b = polartocart(radius, alpha, beta + sst);
			tuple<float, float, float> c = polartocart(radius, alpha + ssl, beta + sst);
			tuple<float, float, float> d = polartocart(radius, alpha + ssl, beta);

			add_point(a, sphere_points);
			add_point(b, sphere_points);
			add_point(c, sphere_points);

			add_point(a, sphere_points);
			add_point(c, sphere_points);
			add_point(d, sphere_points);

			alpha += ssl;
		}
		beta += sst;
		alpha = 0;
	}
	return sphere_points;
}

/*
* Função que cria um array de pontos para contruir um cone
*/
t_points* create_cone(float radius, float height, int slices, int stacks) {
	t_points* cone_points= (t_points*)malloc(sizeof(struct t_points));

	cone_points->size = 6 * slices * stacks + 3 * slices;
	int size = cone_points->size;

	cone_points->points = (tuple<float, float, float>*) malloc(sizeof(tuple<float, float, float>) * size);

	double step = (2 * M_PI) / slices;
	double alpha = 0;
	double beta = atan(height / radius);
	double l = radius / cos(beta);
	double rstep = l / stacks;

	int x = 0, y = height, z = 0;
	double r = 0;
	beta = -beta;
	for (int i = 0; i < stacks; i++)
	{
		alpha = 0;
		for (int i = 0; i < slices; i++)
		{
			tuple<float, float, float> a = polartocart(r, alpha, beta);
			tuple<float, float, float> b = polartocart(r + rstep, alpha, beta);
			tuple<float, float, float> c = polartocart(r, alpha + step, beta);
			tuple<float, float, float> d = polartocart(r + rstep, alpha + step, beta);

			add_point(tuple<float, float, float>(get<0>(a), get<1>(a) + y, get<2>(a)), cone_points); //a
			add_point(tuple<float, float, float>(get<0>(b), get<1>(b) + y, get<2>(b)), cone_points); //b
			add_point(tuple<float, float, float>(get<0>(c), get<1>(c) + y, get<2>(c)), cone_points); //c

			add_point(tuple<float, float, float>(get<0>(b), get<1>(b) + y, get<2>(b)), cone_points); //b
			add_point(tuple<float, float, float>(get<0>(d), get<1>(d) + y, get<2>(d)), cone_points); //d
			add_point(tuple<float, float, float>(get<0>(c), get<1>(c) + y, get<2>(c)), cone_points); //c

			alpha += step;
		}
		r += rstep;
	}
	y = 0;
	beta = 0;
	for (int i = 0; i < slices; i++)
	{
		add_point(tuple<float, float, float>(x, y, z), cone_points);
		add_point(tuple<float, float, float>(x + radius * cos(beta) * sin(alpha), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha)), cone_points);
		add_point(tuple<float, float, float>(x + radius * cos(beta) * sin(alpha - step), y + radius * sin(beta), z + radius * cos(beta) * cos(alpha - step)), cone_points);

		alpha += step;
	}

	return cone_points;
}