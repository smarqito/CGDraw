#include "Model.h"


Model::Model(XMLElement* xml_model)
{
	_xml_model = xml_model;
	_init();
}

void Model::_init() {
	_model_path = (char*)_xml_model->FindAttribute("file")->Value();
	read_points();
}

void Model::read_points()
{
	XMLDocument doc;
	doc.LoadFile(_model_path);
	if (doc.Error()) {
		throw doc.ErrorID();
	}

	XMLElement* x_root = doc.FirstChild()->ToElement();

	_type = x_root->FindAttribute("type")->IntValue();
	int size = x_root->FindAttribute("size")->IntValue();

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




GLenum Model::getType() {
	return _type;
}

char* Model::getFilename() {
	return strdup(_model_path);
}

int Model::size() {
	return _points.size();
}

bool Model::add_point(double x, double y, double z) {
	_points.add_point(x, y, z);
}

point Model::get_next_point() {
	// TODO - implement Model::get_next_point
	throw "Not yet implemented";
}

void Model::_draw() {
	// to add texture
	// to add color
	glBegin(_type);
	_points._draw();
	glEnd();
}