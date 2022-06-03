#include "shapes.h"

std::tuple<t_points, t_points, std::vector<float>> create_plane(float length, int divisions) {
	t_points p_points(6 * pow(divisions, 2));
	t_points p_normals(6 * pow(divisions, 2));
	std::vector<float> p_textures;

	float x = - length / 2;
	float z = - length / 2;
	float step = length / divisions;
	float stepTex = 1.0 / divisions;

	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {
			p_points.add_point(x, 0, z);
			p_points.add_point(x, 0, z + step);
			p_points.add_point(x + step, 0, z);

			p_normals.add_point(0,1,0);
			p_normals.add_point(0,1,0);
			p_normals.add_point(0,1,0);

			p_textures.push_back(j * stepTex); p_textures.push_back(j * stepTex);
			p_textures.push_back(j * stepTex); p_textures.push_back((j * stepTex) + stepTex);
			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back(j * stepTex);

			p_points.add_point(x + step, 0, z);
			p_points.add_point(x, 0, z + step);
			p_points.add_point(x + step, 0, z + step);

			p_normals.add_point(0, 1, 0);
			p_normals.add_point(0, 1, 0);
			p_normals.add_point(0, 1, 0);

			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back(j * stepTex);
			p_textures.push_back(j * stepTex); p_textures.push_back((j * stepTex) + stepTex);
			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back((j * stepTex) + stepTex);

			z += step;
		}
		x += step;
		z = - length / 2; //volta ao valor inicial
	}
	std::tuple<t_points, t_points, std::vector<float>> res(p_points, p_normals, p_textures);
	return res;
}


std::tuple<t_points, t_points, std::vector<float>> create_box(float units, int divisions) {
	t_points p_points(3 * pow(divisions, 2) * 12);
	t_points p_normals(3 * pow(divisions, 2) * 12);
	std::vector<float> p_textures;

	float z = - units / 2;
	float x = - units / 2;
	float y = units / 2;

	float step = units / divisions;
	float stepTex = 1.0 / divisions;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {

			//face inferior
			p_points.add_point(x, -y, z);
			p_points.add_point(x + step, -y, z);
			p_points.add_point(x, -y, z + step);

			p_normals.add_point(0, -1, 0);
			p_normals.add_point(0, -1, 0);
			p_normals.add_point(0, -1, 0);

			p_textures.push_back((j * stepTex)); p_textures.push_back((j * stepTex));
			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back((j * stepTex));
			p_textures.push_back((j * stepTex)); p_textures.push_back((j * stepTex) + stepTex);

			p_points.add_point(x + step, -y, z);
			p_points.add_point(x + step, -y, z + step);
			p_points.add_point(x, -y, z + step);

			p_normals.add_point(0, -1, 0);
			p_normals.add_point(0, -1, 0);
			p_normals.add_point(0, -1, 0);

			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back((j * stepTex));
			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back((j * stepTex) + stepTex);
			p_textures.push_back((j * stepTex)); p_textures.push_back((j * stepTex) + stepTex);

			//face superior

			p_points.add_point(x, y, z);
			p_points.add_point(x, y, z + step);
			p_points.add_point(x + step, y, z);

			p_normals.add_point(0, 1, 0);
			p_normals.add_point(0, 1, 0);
			p_normals.add_point(0, 1, 0);

			p_textures.push_back(j * stepTex); p_textures.push_back(j * stepTex);
			p_textures.push_back(j * stepTex); p_textures.push_back((j * stepTex) + stepTex);
			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back(j * stepTex);

			p_points.add_point(x + step, y, z);
			p_points.add_point(x, y, z + step);
			p_points.add_point(x + step, y, z + step);
			
			p_normals.add_point(0, 1, 0);
			p_normals.add_point(0, 1, 0);
			p_normals.add_point(0, 1, 0);

			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back(j * stepTex);
			p_textures.push_back(j * stepTex); p_textures.push_back((j * stepTex) + stepTex);
			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back((j * stepTex) + stepTex);

			z += step;
		}
		x += step;
		z = - units / 2; //volta ao valor inicial
	}

	x = units / 2;
	y = - units / 2;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {

			//face lateral X positivo
			p_points.add_point(x, y, z);
			p_points.add_point(x, y + step, z);
			p_points.add_point(x, y, z + step);

			p_normals.add_point(1, 0, 0);
			p_normals.add_point(1, 0, 0);
			p_normals.add_point(1, 0, 0);

			p_textures.push_back(j * stepTex); p_textures.push_back(j * stepTex);
			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back(j * stepTex);
			p_textures.push_back(j * stepTex); p_textures.push_back((j * stepTex) + stepTex);

			p_points.add_point(x, y + step, z);
			p_points.add_point(x, y + step, z + step);
			p_points.add_point(x, y, z + step);

			p_normals.add_point(1, 0, 0);
			p_normals.add_point(1, 0, 0);
			p_normals.add_point(1, 0, 0);

			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back(j * stepTex);
			p_textures.push_back((j * stepTex) + stepTex); p_textures.push_back((j * stepTex) + stepTex);
			p_textures.push_back(j * stepTex); p_textures.push_back((j * stepTex) + stepTex);

			//face lateral X negativo
			p_points.add_point(-x, y + step, z);
			p_points.add_point(-x, y, z);
			p_points.add_point(-x, y, z + step);

			p_normals.add_point(-1, 0, 0);
			p_normals.add_point(-1, 0, 0);
			p_normals.add_point(-1, 0, 0);

			p_textures.push_back((j* stepTex) + stepTex); p_textures.push_back(j* stepTex);
			p_textures.push_back(j* stepTex); p_textures.push_back(j* stepTex);
			p_textures.push_back(j* stepTex); p_textures.push_back((j* stepTex) + stepTex);

			p_points.add_point(-x, y + step, z + step);
			p_points.add_point(-x, y + step, z);
			p_points.add_point(-x, y, z + step);

			p_normals.add_point(-1, 0, 0);
			p_normals.add_point(-1, 0, 0);
			p_normals.add_point(-1, 0, 0);

			p_textures.push_back((j* stepTex) + stepTex); p_textures.push_back((j* stepTex) + stepTex);
			p_textures.push_back((j* stepTex) + stepTex); p_textures.push_back(j* stepTex);
			p_textures.push_back(j* stepTex); p_textures.push_back((j* stepTex) + stepTex);

			y += step;
		}
		z += step;
		y = - units / 2; //volta ao valor inicial
	}
	z = units / 2;
	x = -units / 2;
	for (int i = 0; i < divisions; i++) {
		for (int j = 0; j < divisions; j++) {
			//face lateral Z positivo
			p_points.add_point(x, y, z);
			p_points.add_point(x + step, y, z);
			p_points.add_point(x, y + step, z);

			p_normals.add_point(0, 0, 1);
			p_normals.add_point(0, 0, 1);
			p_normals.add_point(0, 0, 1);

			p_textures.push_back(i* stepTex); p_textures.push_back(i* stepTex);
			p_textures.push_back((i* stepTex) + stepTex); p_textures.push_back(i* stepTex);
			p_textures.push_back(i* stepTex); p_textures.push_back((i* stepTex) + stepTex);

			p_points.add_point(x, y + step, z);
			p_points.add_point(x + step, y, z);
			p_points.add_point(x + step, y + step, z);

			p_normals.add_point(1, 0, 0);
			p_normals.add_point(1, 0, 0);
			p_normals.add_point(1, 0, 0);

			p_textures.push_back((i* stepTex) + stepTex); p_textures.push_back(i* stepTex);
			p_textures.push_back(i* stepTex); p_textures.push_back((i* stepTex) + stepTex);
			p_textures.push_back((i* stepTex) + stepTex); p_textures.push_back((i* stepTex) + stepTex);

			//face lateral Z negativo
			p_points.add_point(x, y, -z);
			p_points.add_point(x, y + step, -z);
			p_points.add_point(x + step, y, -z);

			p_normals.add_point(0, 0, -1);
			p_normals.add_point(0, 0, -1);
			p_normals.add_point(0, 0, -1);

			p_textures.push_back(j* stepTex); p_textures.push_back(j* stepTex);
			p_textures.push_back((j* stepTex)); p_textures.push_back((j* stepTex) + stepTex);
			p_textures.push_back((j* stepTex) + stepTex); p_textures.push_back((j* stepTex));

			p_points.add_point(x, y + step, -z);
			p_points.add_point(x + step, y + step, -z);
			p_points.add_point(x + step, y, -z);

			p_normals.add_point(0, 0, -1);
			p_normals.add_point(0, 0, -1);
			p_normals.add_point(0, 0, -1);

			p_textures.push_back(j* stepTex); p_textures.push_back((j* stepTex)+stepTex);
			p_textures.push_back((j* stepTex)+stepTex); p_textures.push_back((j* stepTex)+stepTex);
			p_textures.push_back((j* stepTex)+stepTex); p_textures.push_back((j* stepTex));

			y += step;
		}
		x += step;
		y = - units / 2; //volta ao valor inicial
	}
	std::tuple<t_points, t_points, std::vector<float>> res(p_points, p_normals, p_textures);
	return res;
}

std::tuple<t_points, t_points, std::vector<float>> create_sphere(int radius, int slices, int stacks) {
	t_points p_points(6 * stacks * slices);
	t_points p_normals(6 * stacks * slices);
	std::vector<float> p_textures;

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

				Point norm_a = a;
				normalize(&norm_a);
				Point norm_c = c;
				normalize(&norm_c);
				Point norm_d = d;
				normalize(&norm_d);

				p_normals.add_point(norm_a);
				p_normals.add_point(norm_c);
				p_normals.add_point(norm_d);

			}
			else if (i == 0) {
				p_points.add_point(a);
				p_points.add_point(b);
				p_points.add_point(c);

				Point norm_a = a;
				normalize(&norm_a);
				Point norm_b = b;
				normalize(&norm_b);
				Point norm_d = d;
				normalize(&norm_d);

				p_normals.add_point(norm_a);
				p_normals.add_point(norm_b);
				p_normals.add_point(norm_d);

			}
			else {
				p_points.add_point(a);
				p_points.add_point(b);
				p_points.add_point(c);
				p_points.add_point(a);
				p_points.add_point(c);
				p_points.add_point(d);

				Point norm_a = a;
				normalize(&norm_a);
				Point norm_b = b;
				normalize(&norm_b);
				Point norm_c = c;
				normalize(&norm_c);
				Point norm_d = d;
				normalize(&norm_d);

				p_normals.add_point(norm_a);
				p_normals.add_point(norm_b);
				p_normals.add_point(norm_c);
				p_normals.add_point(norm_a);
				p_normals.add_point(norm_c);
				p_normals.add_point(norm_d);

			}

			alpha += ssl;
		}
		beta -= sst;
		alpha = 0;
	}
	std::tuple<t_points, t_points, std::vector<float>> res(p_points, p_normals, p_textures);
	return res;
}

std::tuple<t_points, t_points, std::vector<float>> create_cylinder(int radius, int height, int slices, int stacks)
{
	t_points p_points(6 * slices + 6 * slices * stacks);
	t_points p_normals(6 * slices + 6 * slices * stacks);
	std::vector<float> p_textures;

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

		p_normals.add_point(0, 1, 0);
		p_normals.add_point(0, 1, 0);
		p_normals.add_point(0, 1, 0);

		p_textures.push_back(0.5); p_textures.push_back(0.5);
		p_textures.push_back(0.5 + cos(alpha)); p_textures.push_back(0.5 + sin(alpha));
		p_textures.push_back(0.5 + cos(alpha + ssl)); p_textures.push_back(0.5 + sin(alpha + ssl));

		p_points.add_point(x + b.x, y - b.y - height, z + b.z);
		p_points.add_point(x + a.x, y - height + a.y, z + a.z);
		p_points.add_point(x, y - height, z);

		p_normals.add_point(0, -1, 0);
		p_normals.add_point(0, -1, 0);
		p_normals.add_point(0, -1, 0);

		p_textures.push_back(0.5); p_textures.push_back(0.5);
		p_textures.push_back(0.5 + cos(alpha)); p_textures.push_back(0.5 + sin(alpha));
		p_textures.push_back(0.5 + cos(alpha - ssl)); p_textures.push_back(0.5 + sin(alpha + ssl));

		alpha += ssl;
	}
	alpha = 0;

	float step_x = 1 / slices;
	float step_y = 1 / stacks;
	for (int i = 0; i < stacks; i++) {
		for (int j = 0; j < slices; j++)
		{
			Point a = polartocart(radius, alpha, beta);
			Point b = polartocart(radius, alpha + ssl, beta);

			p_points.add_point(b.x, y + b.y - sst, b.z);
			p_points.add_point(b.x, y + b.y, b.z);
			p_points.add_point(a.x, y + a.y, a.z);

			p_normals.add_point(sin(alpha + ssl), 0, cos(alpha+ssl));
			p_normals.add_point(sin(alpha + ssl), 0, cos(alpha+ssl));
			p_normals.add_point(sin(alpha), 0, cos(alpha));

			p_textures.push_back(1-((j+1) * step_x)); p_textures.push_back(1-((i+1) * step_y));
			p_textures.push_back(1 - ((j + 1) * step_x)); p_textures.push_back(1 - (i * step_y));
			p_textures.push_back(1 - (j * step_x)); p_textures.push_back(1 - (i * step_y));

			p_points.add_point(a.x, y + a.y, a.z);
			p_points.add_point(a.x, y + a.y - sst, a.z);
			p_points.add_point(b.x, y + b.y - sst, b.z);

			p_normals.add_point(sin(alpha), 0, cos(alpha));
			p_normals.add_point(sin(alpha), 0, cos(alpha));
			p_normals.add_point(sin(alpha+ssl), 0, cos(alpha+ssl));

			p_textures.push_back(1 - (j * step_x)); p_textures.push_back(1 - (i * step_y));
			p_textures.push_back(1 - (j * step_x)); p_textures.push_back(1 - ((i + 1) * step_y));
			p_textures.push_back(1 - ((j + 1) * step_x)); p_textures.push_back(1 - ((i + 1) * step_y));

			alpha += ssl;
		}
		y -= sst;
		alpha = 0;
	}
	std::tuple<t_points, t_points, std::vector<float>> res(p_points, p_normals, p_textures);
	return res;
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



t_points create_bezier(std::vector<std::vector<int>> patches, std::vector<Point> all_points, int level) {
	float step = 1.0 / level;

	Matrix bezier(BEZIER);
	BezierTriangles p(4, 4, bezier);

	t_points res(patches.size() * level * level * 6);
	std::vector<int> indices;
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
				res.add_point(u1v0);
				res.add_point(u1v0);
				res.add_point(u0v1);
				res.add_point(u1v1);
			}
		}
	}
	return res;
}

std::tuple<t_points, t_points, std::vector<float>> create_sphere(int radius, int slices, int stacks, Point offset) {
	t_points p_points(6 * stacks * slices);
	t_points p_normals(6 * stacks * slices);
	std::vector<float> p_textures; 

	float sst = M_PI / stacks;
	float ssl = 2 * M_PI / slices;
	float beta = M_PI / 2;
	float alpha = 0;

	for (int i = 0; i < stacks; i++)
	{
		for (int j = 0; j < slices; j++)
		{
			Point a = polartocart(radius, alpha, beta);
			a.x += offset.x; a.y += offset.y; a.z += offset.z;
			Point b = polartocart(radius, alpha, beta - sst);
			b.x += offset.x; b.y += offset.y; b.z += offset.z;
			Point c = polartocart(radius, alpha + ssl, beta - sst);
			c.x += offset.x; c.y += offset.y; c.z += offset.z;
			Point d = polartocart(radius, alpha + ssl, beta);
			d.x += offset.x; d.y += offset.y; d.z += offset.z;

			if (i == stacks - 1) {
				p_points.add_point(a);
				p_points.add_point(c);
				p_points.add_point(d);

				Point norm_a = sub_points(a, offset);
				normalize(&norm_a);
				Point norm_c = sub_points(c, offset);
				normalize(&norm_c);
				Point norm_d = sub_points(d, offset);
				normalize(&norm_d);

				p_normals.add_point(norm_a);
				p_normals.add_point(norm_c);
				p_normals.add_point(norm_d);
			}
			else if (i == 0) {
				p_points.add_point(a);
				p_points.add_point(b);
				p_points.add_point(c);

				Point norm_a = sub_points(a, offset);
				normalize(&norm_a);
				Point norm_b = sub_points(b, offset);
				normalize(&norm_b);
				Point norm_c = sub_points(c, offset);
				normalize(&norm_c);

				p_normals.add_point(norm_a);
				p_normals.add_point(norm_b);
				p_normals.add_point(norm_c);
			}
			else {
				p_points.add_point(a);
				p_points.add_point(b);
				p_points.add_point(c);
				p_points.add_point(a);
				p_points.add_point(c);
				p_points.add_point(d);

				Point norm_a = sub_points(a, offset);
				normalize(&norm_a);
				Point norm_b = sub_points(b, offset);
				normalize(&norm_b);
				Point norm_c = sub_points(c, offset);
				normalize(&norm_c);
				Point norm_d = sub_points(d, offset);
				normalize(&norm_d);

				p_normals.add_point(norm_a);
				p_normals.add_point(norm_b);
				p_normals.add_point(norm_c);
				p_normals.add_point(norm_a);
				p_normals.add_point(norm_c);
				p_normals.add_point(norm_d);

			}

			alpha += ssl;
		}
		beta -= sst;
		alpha = 0;
	}
	std::tuple<t_points, t_points, std::vector<float>> res(p_points, p_normals, p_textures);
	return res
}

t_points create_asteroids(double distMin, double distMax, int maxSize, int slices, int stacks, double alphaMax, double betaMax, int numAsteroids) {
	t_points p_points(numAsteroids * 6 * stacks * slices);
	srand(1);
	for (int i = 0; i < numAsteroids; i++) {
		int raio = distMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (distMax - distMin)));
		double alpha = static_cast <float> (rand()) / (static_cast <float>(RAND_MAX / alphaMax)) * M_PI / 180;
		double beta = (-betaMax + static_cast <float> (rand()) / (static_cast <float>(RAND_MAX / (2 * betaMax)))) * M_PI / 180;
		
		Point p = polartocart(raio, alpha, beta);

		int size = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / maxSize));
		t_points res = create_sphere(size, slices, stacks, p);
		p_points.add_points(res);

	}
	return p_points;
}