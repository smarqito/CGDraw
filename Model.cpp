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

void Model::read_points()
{
	vector<float> points;
	XMLDocument doc;
	doc.LoadFile(_model_path.c_str());
	if (doc.Error()) {
		throw doc.ErrorID();
	}

	XMLElement* x_root = doc.FirstChild()->ToElement();

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
		points.push_back(x);
		points.push_back(y);
		points.push_back(z);
		pPoint = pPoint->NextSiblingElement("point");
	}
	//glGenBuffers(1, buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	//glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
//	build_vbo();
}

void Model::build_vbo() {
	point* vetor = _points.get_points_ptr();
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
	//glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	//glVertexPointer(3, GL_FLOAT, 0, 0);
	//glDrawArrays(_type, 0, _points.total() * 3);
	glBegin(_type);
	for (int i = 0; i < this->size(); i++) {
		p = points[i];
		glVertex3d(p.x, p.y, p.z);
	}
	//_points._draw();
	glEnd();
}