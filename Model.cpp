#include "Model.h"
#include "CGDraw.h"
#include "Common.h"
#include <bits/stdc++.h>

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
	bool indexes = x_root->FindAttribute("indexes")->BoolValue();
	double level = x_root->FindAttribute("bezier")->DoubleValue();
	//_points = t_points(size);
	if (indexes) {
		XMLElement* pIndexes = x_root->FirstChildElement("indexes");
		XMLElement* pIndex = pIndexes->FirstChildElement("index");

		for (int i = 0; pIndex != NULL; i++) {
			const char* text = pIndex->GetText();
			stringstream ss(text);
			vector<unsigned int> index_row;
			while (ss.good()) {
				string substr;
				getline(ss, substr, ',');
				index_row.push_back(stoi(substr));
			}
			GLuint ind;
			glGenBuffers(1, &ind);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				sizeof(unsigned int) * index_row.size(),
				index_row.data(),
				GL_STATIC_DRAW);
			_indexes_count.push_back(index_row.size());
			_indexes.push_back(ind);
			pIndex = pIndex->NextSiblingElement("index");
		}
	}
	XMLElement* pPoints = x_root->FirstChildElement("points");
	XMLElement* pPoint = pPoints->FirstChildElement("point");

	double x, y, z;
	vector<point> points_vector;
	while (pPoint != NULL) {
		x = pPoint->FindAttribute("x")->DoubleValue();
		y = pPoint->FindAttribute("y")->DoubleValue();
		z = pPoint->FindAttribute("z")->DoubleValue();
		//add_point(x, y, z);
		points.push_back(x);
		points.push_back(y);
		points.push_back(z);
		point p;
		p.x = x; p.y = y; p.z = z;
		points_vector.push_back(p);
		pPoint = pPoint->NextSiblingElement("point");
	}
	if (level != 0.0) {
		vector<float> res;
		float pos[4];
		float deriv[4];
		double step = 1.0 / level;
		for (double i = 0.0; i < 1; i += step) {
			getGlobalCatmullRomPoint(i, pos, deriv, points_vector);
			res.push_back(pos[0]);
			res.push_back(pos[1]);
			res.push_back(pos[2]);
		}
		_total_points = res.size();
		glGenBuffers(1, &_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glBufferData(GL_ARRAY_BUFFER, res.size() * sizeof(float), res.data(), GL_STATIC_DRAW);
	}
	else {
		_total_points = points.size();
		glGenBuffers(1, &_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
	}
//	build_vbo();
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
	// to add texture
	// to add color
	//point* points = _points.get_points_ptr();
	point p;
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	if (_indexes.size() != 0) {
		for (int i = 0; i < _indexes.size(); i++) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexes[i]);
			glDrawElements(_type, _indexes_count[i], GL_UNSIGNED_INT, 0);
		}

	}
	else {
		glDrawArrays(_type, 0, _total_points * 3);
	}
	//glBegin(_type);
	//for (int i = 0; i < this->size(); i++) {
	//	p = points[i];
	//	glVertex3d(p.x, p.y, p.z);
	//}
	////_points._draw();
	//glEnd();
}