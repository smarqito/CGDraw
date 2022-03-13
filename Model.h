#pragma once
#include <GL/glut.h>
#include "generator/shapes.h"
#include <string.h>
#include "cartesian/cartesian.h"

using namespace std;

class Model {

private:
	t_points points;
	GLenum type;
	XMLElement* xml_elem;
	//texture texture;
	//color color;

public:
	Model(int size, XMLElement* xml_elem);

	void _init() {
		this->type = xml_elem->FindAttribute("type")->IntValue();
		int size = xml_elem->FindAttribute("size")->IntValue();
		//Model m = Model(type, size, path);
		XMLElement* pPoint = xml_elem->FirstChildElement("point");
		for (int i = 0; pPoint != NULL; i++) {
			float x = pPoint->FindAttribute("x")->FloatValue();
			float y = pPoint->FindAttribute("y")->FloatValue();
			float z = pPoint->FindAttribute("z")->FloatValue();
			pPoint = pPoint->NextSiblingElement();
		}
	}

	GLenum getType();

	string getFilename();

	int size();

	bool add_point(double x, double y, double z);

	point get_next_point();

	void _draw() {
		glBegin(this->type);
		this->points._draw();
	}
};
