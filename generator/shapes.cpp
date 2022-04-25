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
			p_points.add_point(x, -units / 2, z);
			p_points.add_point(x - step, -units / 2, z);
			p_points.add_point(x, -units / 2, z - step);

			p_points.add_point(x - step, -units / 2, z);
			p_points.add_point(x - step, -units / 2, z - step);
			p_points.add_point(x, -units / 2, z - step);

			//face superior

			p_points.add_point(x, units / 2, z);
			p_points.add_point(x, units / 2, z - step);
			p_points.add_point(x - step, units / 2, z);

			p_points.add_point(x - step, units / 2, z);
			p_points.add_point(x, units / 2, z - step);
			p_points.add_point(x - step, units / 2, z - step);

			z -= step;
		}
		x -= step;
		z = units / 2; //volta ao valor inicial
	}

	x = units / 2;
	double y = units / 2;
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
		y = units / 2; //volta ao valor inicial
	}
	z = units / 2;
	y = units / 2;
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
		y = units / 2; //volta ao valor inicial
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

	double ssl = 2 * M_PI / slices;
	double sst = (double)height / stacks;
	double alpha = 0;
	double beta = 0;
	double x = 0, y = (double)height / 2, z = 0;
	for (int i = 0; i < slices; i++)
	{
		point a = polartocart(radius, alpha, beta);
		point b = polartocart(radius, alpha + ssl, beta);
		p_points.add_point(x, y, z);
		p_points.add_point(x + a.x, y + a.y, z + a.z);
		p_points.add_point(x + b.x, y + b.y, z + b.z);

		p_points.add_point(x + b.x, y - b.y - height, z + b.z);
		p_points.add_point(x + a.x, y - height + a.y, z + a.z);
		p_points.add_point(x, y - height, z);

		alpha += ssl;
	}
	alpha = 0;

	for (int i = 0; i < stacks; i++) {
		for (int j = 0; j < slices; j++)
		{
			point a = polartocart(radius, alpha, beta);
			point b = polartocart(radius, alpha + ssl, beta);

			p_points.add_point(b.x, y + b.y - sst, b.z);
			p_points.add_point(b.x, y + b.y, b.z);
			p_points.add_point(a.x, y + a.y, a.z);

			p_points.add_point(a.x, y + a.y, a.z);
			p_points.add_point(a.x, y + a.y - sst, a.z);
			p_points.add_point(b.x, y + b.y - sst, b.z);
			alpha += ssl;
		}
		y -= sst;
		alpha = 0;
	}
	return p_points;
}

t_points create_torus(double radius, double size, int slices, int stack) {
	t_points p_points(12 * slices * stack + 2 * slices);

	double ssl = (2 * M_PI) / slices;
	double sst = M_PI / stack;
	double alpha = 0;
	double beta = -M_PI/2;
	double x = 0, y = 0, z = 0;

	for (int j = 0; j < slices; j++) {
		for (int i = 0; i < stack; i++) {
			point a = polartocart(radius, alpha, 0);
			point a1 = polartocart(size, alpha, beta);
			point a2 = polartocart(size, alpha, beta+sst);
			
			point b = polartocart(radius, alpha + ssl, 0);
			point b1 = polartocart(size, alpha+ssl, beta);
			point b2 = polartocart(size, alpha+ssl, beta + sst);

			p_points.add_point(sum_points(a, a1));
			p_points.add_point(sum_points(b, b1));
			p_points.add_point(sum_points(b, b2));

			p_points.add_point(sum_points(a, a1));
			p_points.add_point(sum_points(b, b2));
			p_points.add_point(sum_points(a, a2));

			p_points.add_point(sub_points(a, a1));
			p_points.add_point(sub_points(b, b1));
			p_points.add_point(sub_points(b, b2));

			p_points.add_point(sub_points(a, a1));
			p_points.add_point(sub_points(b, b2));
			p_points.add_point(sub_points(a, a2));

			beta += sst;
		}
		alpha += ssl;
		beta = -M_PI/2;
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
		point c = polartocart(radius, alpha - step, beta);
		p_points.add_point(x, y, z);
		p_points.add_point(x + b.x, y + b.y, z + b.z);
		p_points.add_point(x + c.x, y + c.y, z + c.z);

		alpha += step;
	}

	return p_points;
}

vector<t_points> create_bezier(vector<vector<int>> patches, vector<point> all_points, int level) {
	float step = 1.0 / level;
	
	float pos_[3];
	float deriv_[3];
	matrix pos = {
		pos_, 1, 3
	};
	matrix deriv = {
		deriv_, 1, 3
	};
	
	Curve c;
	c.addControlPoint(all_points);

	vector<t_points> res;
	for (int i = 0; i < patches.size(); i++) {
		t_points p_points(level);
		vector<point> p;
		for (float j = 0; j < 1; j += step) {
			c.getPoint(j, patches[i], &pos, &deriv);
			p_points.add_point(pos.mat[0], pos.mat[1], pos.mat[2]);
		}
		res.push_back(p_points);
	}
	return res;

}