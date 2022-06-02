#include "Model.h"
#include "CGDraw.h"
#include "Common.h"
#include "ModelTexture.h"

Model::Model(XMLElement* xml_model)
{
	_xml_model = xml_model;
	_n_buffers = 0;
	_init();
}

void Model::_init() {
	std::string t = std::string(file_path);
	_model_path = t + std::string(_xml_model->FindAttribute("file")->Value());
	read_points();

	XMLElement* colorElem;
	if ((colorElem = _xml_model->FirstChildElement("color")) != NULL) {
		_color = Color(colorElem);
	}
}

void Model::read_points_basic(XMLElement* x_root)
{
	vector<float> points;
	_buffer = (GLuint*)malloc(sizeof(GLuint));
	_total_points = (GLint*)malloc(sizeof(GLint));
	_type = x_root->FindAttribute("type")->IntValue();
	int size = x_root->FindAttribute("size")->IntValue();
	//_points = t_points(size);
	XMLElement* pPoint = x_root->FirstChildElement("point");

	double x, y, z;

	while (pPoint != NULL) {
		x = pPoint->FindAttribute("x")->DoubleValue();
		y = pPoint->FindAttribute("y")->DoubleValue();
		z = pPoint->FindAttribute("z")->DoubleValue();
		//add_point(x, y, z);
		points.push_back(x);
		points.push_back(y);
		points.push_back(z);
		pPoint = pPoint->NextSiblingElement("point");
	}
	_total_points[0] = points.size();
	_n_buffers = 1;
	glGenBuffers(1, _buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

}

void Model::read_points_patch(XMLElement* x_root)
{
	_type = x_root->FindAttribute("type")->IntValue();
	int size = x_root->FindAttribute("size")->IntValue();
	_buffer = (GLuint*)malloc(sizeof(GLuint) * size);
	_total_points = (GLint*)malloc(sizeof(GLint) * size);
	_n_buffers = size;
	glGenBuffers(size, _buffer);
	std::vector<float> points;
	XMLElement* pPatch = x_root->FirstChildElement("patch");
	XMLElement* pPoint;
	float x, y, z;
	int n_points;
	for (int i = 0; i < size && pPatch != NULL; i++)
	{
		pPoint = pPatch->FirstChildElement("point");
		n_points = 0;
		while (pPoint != NULL) {
			x = pPoint->FindAttribute("x")->FloatValue();
			y = pPoint->FindAttribute("y")->FloatValue();
			z = pPoint->FindAttribute("z")->FloatValue();
			//add_point(x, y, z);
			points.push_back(x);
			points.push_back(y);
			points.push_back(z);
			pPoint = pPoint->NextSiblingElement("point");
			n_points++;
		}
		_total_points[i] = n_points;
		glBindBuffer(GL_ARRAY_BUFFER, _buffer[i]);
		glBufferData(
			GL_ARRAY_BUFFER,
			points.size() * sizeof(float),
			points.data(),
			GL_STATIC_DRAW
		);
		points.clear();
		pPatch = pPatch->NextSiblingElement("patch");
	}
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
	XMLElement* textures;
	if ((textures = x_root->FirstChildElement("textures")) != NULL) {
		_texture = ModelTexture(_xml_model->FirstChildElement("texture"), textures);
	}
}

GLenum Model::getType() {
	return _type;
}

char* Model::getFilename() {
	return strdup(_model_path.c_str());
}

//int Model::size() {
//	return _points.size();
//}

//bool Model::add_point(double x, double y, double z) {
//	return _points.add_point(x, y, z);
//}

void Model::_draw() {
	// Drawing color first
	_color._draw();
	// to add texture
	//Point p;
	for (int i = 0; i < _n_buffers; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _buffer[i]);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawArrays(_type, 0, _total_points[i] * 3);

		_normals._draw();
		_texture.draw();

	}

}