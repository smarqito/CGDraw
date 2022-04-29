#include "shapes.h"

t_points create_plane(float length, int divisions) {
	t_points p_points(6 * pow(divisions, 2));

	float x = length / 2;
	float z = length / 2;
	float step = length / divisions;

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


t_points create_box(float units, int divisions) {
	t_points p_points(3 * pow(divisions, 2) * 12);

	float z = units / 2;
	float x = units / 2;

	float step = units / divisions;
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
	float y = units / 2;
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

	float sst = M_PI / stacks;
	float ssl = 2 * M_PI / slices;
	float beta = M_PI / 2;
	float alpha = 0;

	for (int i = 0; i < stacks; i++)
	{
		for (int j = 0; j < slices; j++)
		{
			Point a = polartocart(radius, alpha, beta);
			Point b = polartocart(radius, alpha, beta - sst);
			Point c = polartocart(radius, alpha + ssl, beta - sst);
			Point d = polartocart(radius, alpha + ssl, beta);

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
	float sst = (float)height / stacks;
	float alpha = 0;
	float beta = 0;
	float x = 0, y = (float)height / 2, z = 0;
	for (int i = 0; i < slices; i++)
	{
		Point a = polartocart(radius, alpha, beta);
		Point b = polartocart(radius, alpha + ssl, beta);
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
			Point a = polartocart(radius, alpha, beta);
			Point b = polartocart(radius, alpha + ssl, beta);

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

t_points create_torus(float radius, float size, int slices, int stack) {
	t_points p_points(12 * slices * stack + 2 * slices);

	float ssl = (2 * M_PI) / slices;
	float sst = M_PI / stack;
	float alpha = 0;
	float beta = -M_PI / 2;
	float x = 0, y = 0, z = 0;

	for (int j = 0; j < slices; j++) {
		for (int i = 0; i < stack; i++) {
			Point a = polartocart(radius, alpha, 0);
			Point a1 = polartocart(size, alpha, beta);
			Point a2 = polartocart(size, alpha, beta + sst);

			Point b = polartocart(radius, alpha + ssl, 0);
			Point b1 = polartocart(size, alpha + ssl, beta);
			Point b2 = polartocart(size, alpha + ssl, beta + sst);

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
		beta = -M_PI / 2;
	}
	return p_points;
}

t_points create_cone(float radius, float height, int slices, int stacks) {
	t_points p_points(6 * slices * stacks + 3 * slices);

	float step = (2 * M_PI) / slices;
	float alpha = 0;
	float beta = atan(height / radius);
	float l = radius / cos(beta);
	float rstep = l / stacks;

	int x = 0, y = height, z = 0;
	float r = 0;
	beta = -beta;
	for (int i = 0; i < stacks; i++)
	{
		alpha = 0;
		for (int j = 0; j < slices; j++)
		{
			Point a = polartocart(r, alpha, beta);
			Point b = polartocart(r + rstep, alpha, beta);
			Point c = polartocart(r, alpha + step, beta);
			Point d = polartocart(r + rstep, alpha + step, beta);

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
		Point b = polartocart(radius, alpha, beta);
		Point c = polartocart(radius, alpha - step, beta);
		p_points.add_point(x, y, z);
		p_points.add_point(x + b.x, y + b.y, z + b.z);
		p_points.add_point(x + c.x, y + c.y, z + c.z);

		alpha += step;
	}

	return p_points;
}

t_points create_bezier(vector<vector<int>> patches, vector<Point> all_points, int level) {
	float step = 1.0 / level;

	Matrix bezier(BEZIER);
	BezierTriangles p(4, 4, bezier);

	t_points res(6 * level * level * 3);
	Point u0v0, u0v1, u1v0, u1v1;
	for (int i = 0; i < patches.size(); i++) {
		// add patch points
		for (int j = 0; j < patches[i].size(); j++)
		{
			p.setPatchPoint(j, all_points[patches[i][j]]);
		}
		p.preCalculus();
		for (float u = 0; u < 1; u += step)
		{
			for (float v = 0; v < 1; v += step)
			{
				u0v0 = p.getControlPoint(u, v);
				u1v0 = p.getControlPoint(u + step, v);
				u0v1 = p.getControlPoint(u, v + step);
				u1v1 = p.getControlPoint(u + step, v + step);
				res.add_point(u0v0);
				res.add_point(u0v1);
				res.add_point(u1v1);
				res.add_point(u0v0);
				res.add_point(u1v1);
				res.add_point(u1v0);
			}
		}
	}
	return res;
}