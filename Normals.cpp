#include "Normals.h"

Normals::Normals()
{
}

Normals::Normals(XMLElement* xml_elem)
{
	_xml_element = xml_elem;
	init();
}

void Normals::init()
{
	std::vector<float> normals;
	XMLElement* pPoint = _xml_element->FirstChildElement("ponto");

	double x, y;
	while (pPoint != NULL) {
		x = pPoint->FindAttribute("x")->DoubleValue();
		y = pPoint->FindAttribute("y")->DoubleValue();
		normals.push_back(x);
		normals.push_back(y);
		pPoint = pPoint->NextSiblingElement("ponto");
	}
	glGenBuffers(1, _buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
}

void Normals::_draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	glNormalPointer(GL_FLOAT, 0, 0);
}
