#include "Model.h"
#include "CGDraw.h"
#include "Common.h"

Model::Model(XMLElement* xml_model)
{
	_xml_model = xml_model;
	_init();
}

void Model::_init() {
	string t = string(file_path);
	_model_path = t + string(_xml_model->FindAttribute("file")->Value());
	read_points();
}

void Model::read_points_basic(XMLElement* x_root)
{
	_type = x_root->FindAttribute("type")->IntValue();
	int size = x_root->FindAttribute("size")->IntValue();
	_points = t_points(size);
	XMLElement* pPoint = x_root->FirstChildElement("point");

	double x, y, z;

	while (pPoint != NULL) {
		x = pPoint->FindAttribute("x")->DoubleValue();
		y = pPoint->FindAttribute("y")->DoubleValue();
		z = pPoint->FindAttribute("z")->DoubleValue();
		add_point(x, y, z);
		pPoint = pPoint->NextSiblingElement("point");
	}
}

void Model::read_points_patch(XMLElement* x_root)
{

}

void Model::read_points()
{
	XMLDocument doc;
	doc.LoadFile(_model_path.c_str());
	if (doc.Error()) {
		throw doc.ErrorID();
	}

	XMLElement* x_root = doc.FirstChild()->ToElement();
	if (x_root->BoolAttribute("patches"))
	{
		read_points_patch(x_root);
	}
	else
	{
		read_points_basic(x_root);
	}

}




GLenum Model::getType() {
	return _type;
}

char* Model::getFilename() {
	return strdup(_model_path.c_str());
}

int Model::size() {
	return _points.size();
}

bool Model::add_point(double x, double y, double z) {
	return _points.add_point(x, y, z);
}

point Model::get_next_point() {
	// TODO - implement Model::get_next_point
	throw "Not yet implemented";
}

void Model::_draw() {
	// to add texture
	// to add color

	point* points = _points.get_points_ptr();
	point p;
	glBegin(_type);
	for (int i = 0; i < this->size(); i++) {
		p = points[i];
		glVertex3d(p.x, p.y, p.z);
	}
	//_points._draw();
	glEnd();
}