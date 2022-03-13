#pragma once
#include <GL/glut.h>
#include "generator/shapes.h"
#include <string.h>
#include "cartesian/cartesian.h"

class Model
{
	GLenum type;
	t_points points;
	char* filename;
public:
	Model(GLenum type, int size, char* filename) {
		this->type = type;
		this->filename = strdup(filename);
		points = t_points(size);
	}
	bool addPoint(double x, double y, double z) {
		return points.add_point(x, y, z);
	}

	xyz getNextPoint() {
		return points.get_point();
	}
};
