#include "shapes.h"

t_points create_plane(double length, int divisions) {
	t_points p_points(6 * pow(divisions, 2));

	double x = length / 2;
	double z = length / 2;
	double step = length / divisions;

	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {
			p_points.add_point(x, 0, z);
			p_points.add_point(x, 0, z - step);
			p_points.add_point(x - step, 0, z);

			p_points.add_point(x - step, 0, z);
			p_points.add_point(x, 0, z - step);
			p_points.add_point(x - step, 0, z - step);

			z -= step;
		}
		x -= step;
		z = length / 2; //volta ao valor inicial
	}

	return p_points;
}


t_points create_box(double units, int divisions) {
	t_points p_points(3 * pow(divisions, 2) * 12);

	double z = units / 2;
	double x = units / 2;

	double step = units / divisions;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {

			//face inferior
			p_points.add_point(x, -units/2, z);
			p_points.add_point(x - step, -units/2, z);
			p_points.add_point(x, -units/2, z - step);

			p_points.add_point(x - step, -units/2, z);
			p_points.add_point(x - step, -units/2, z - step);
			p_points.add_point(x, -units/2, z - step);

			//face superior

			p_points.add_point(x, units/2, z);
			p_points.add_point(x, units/2, z - step);
			p_points.add_point(x - step, units/2, z);

			p_points.add_point(x - step, units/2, z);
			p_points.add_point(x, units/2, z - step);
			p_points.add_point(x - step, units/2, z - step);

			z -= step;
		}
		x -= step;
		z = units / 2; //volta ao valor inicial
	}

	x = units / 2;
	double y = units/2;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {

			//face lateral X positivo
			p_points.add_point(x, y, z);
			p_points.add_point(x, y - step, z);
			p_points.add_point(x, y, z - step);

			p_points.add_point(x, y - step, z);
			p_points.add_point(x, y - step, z - step);
			p_points.add_point(x, y, z - step);

			//face lateral X negativo
			p_points.add_point(-x, y - step, z);
			p_points.add_point(-x, y, z);
			p_points.add_point(-x, y, z - step);

			p_points.add_point(-x, y - step, z - step);
			p_points.add_point(-x, y - step, z);
			p_points.add_point(-x, y, z - step);

			y -= step;
		}
		z -= step;
		y = units/2; //volta ao valor inicial
	}
	z = units / 2;
	y = units/2;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {
			//face lateral Y positivo
			p_points.add_point(x, y, z);
			p_points.add_point(x - step, y, z);
			p_points.add_point(x, y - step, z);

			p_points.add_point(x, y - step, z);
			p_points.add_point(x - step, y, z);
			p_points.add_point(x - step, y - step, z);

			//face lateral Y negativo
			p_points.add_point(x, y, -z);
			p_points.add_point(x, y - step, -z);
			p_points.add_point(x - step, y, -z);

			p_points.add_point(x, y - step, -z);
			p_points.add_point(x - step, y - step, -z);
			p_points.add_point(x - step, y, -z);
			y -= step;
		}
		x -= step;
		y = units/2; //volta ao valor inicial
	}

	return p_points;
}

t_points create_sphere(int radius, int slices, int stacks) {
	t_points p_points(6 * stacks * slices);

	double sst = M_PI / stacks;
	double ssl = 2 * M_PI / slices;
	double beta = M_PI / 2;
	double alpha = 0;

	for (int i = 0; i < stacks; i++)
	{
		for (int j = 0; j < slices; j++)
		{
			point a = polartocart(radius, alpha, beta);
			point b = polartocart(radius, alpha, beta - sst);
			point c = polartocart(radius, alpha + ssl, beta - sst);
			point d = polartocart(radius, alpha + ssl, beta);

			if (i == stacks - 1) {
				p_points.add_point(a);
				p_points.add_point(c);
				p_points.add_point(d);
			}
			else if (i == 0) {
				p_points.add_point(a);
				p_points.add_point(b);
				p_points.add_point(c);
			}
			else {
			p_points.add_point(a);
			p_points.add_point(b);
			p_points.add_point(c);
			p_points.add_point(a);
			p_points.add_point(c);
			p_points.add_point(d);

			}

			alpha += ssl;
		}
		beta -= sst;
		alpha = 0;
	}
	return p_points;
}

t_points create_cylinder(int radius, int height, int slices, int stacks)
{
	t_points p_points(6 * slices + 6 * slices * stacks);
	float ssl = 2 * M_PI / slices;
	float sst = height / stacks;
	float alpha = 0;
	float beta = 0;
	float y;
	for (int i = 0; i < slices; i++) {
		float x1 = radius * cos(beta) * sin(alpha);
		float z1 = radius * cos(beta) * cos(alpha);
		float x2 = radius * cos(beta) * sin(alpha + ssl);
		float z2 = radius * cos(beta) * cos(alpha + ssl);
		//Face inferior
		p_points.add_point(x1, -height / 2, z1);
		p_points.add_point(0, -height / 2, 0);
		p_points.add_point(x2, -height / 2, z2);
		//Face superior
		p_points.add_point(0, height / 2, 0);
		p_points.add_point(x1, height / 2, z1);
		p_points.add_point(x2, height / 2, z2);
		//Lados
		y = -height / 2;
		for (int j = 0; j < stacks; j++) {
			p_points.add_point(x1, y + sst, z1);
			p_points.add_point(x1, y, z1);
			p_points.add_point(x2, y, z2);

			p_points.add_point(x2, y + sst, z2);
			p_points.add_point(x1, y + sst, z1);
			p_points.add_point(x2, y, z2);
			y += sst;
		}
		alpha += ssl;
	}
	return p_points;
}

t_points create_cone(double radius, double height, int slices, int stacks) {
	t_points p_points(6 * slices * stacks + 3 * slices);

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
		for (int j = 0; j < slices; j++)
		{
			point a = polartocart(r, alpha, beta);
			point b = polartocart(r + rstep, alpha, beta);
			point c = polartocart(r, alpha + step, beta);
			point d = polartocart(r + rstep, alpha + step, beta);

			p_points.add_point(a.x, a.y + y, a.z); //a
			p_points.add_point(b.x, b.y + y, b.z); //b
			p_points.add_point(c.x, c.y + y, c.z); //c

			p_points.add_point(b.x, b.y + y, b.z); //b
			p_points.add_point(d.x, d.y + y, d.z); //d
			p_points.add_point(c.x, c.y + y, c.z); //c

			alpha += step;
		}
		r += rstep;
	}
	y = 0;
	beta = 0;
	for (int i = 0; i < slices; i++)
	{
		point b = polartocart(radius, alpha, beta);
		point c = polartocart(radius, alpha-step, beta);
		p_points.add_point(x, y, z);
		p_points.add_point(x + b.x, y + b.y, z + b.z);
		p_points.add_point(x + c.x, y + c.y, z + c.z);

		alpha += step;
	}

	return p_points;
}