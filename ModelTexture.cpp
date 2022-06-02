#include "ModelTexture.h"


ModelTexture::ModelTexture()
{
}

ModelTexture::ModelTexture(XMLElement* pontos, XMLElement* texture) : Texture(texture)
{
	vector<float> coords;
	XMLElement* pPoint = texture->FirstChildElement("ponto");

	double x, y;
	while (pPoint != NULL) {
		x = pPoint->FindAttribute("x")->DoubleValue();
		y = pPoint->FindAttribute("y")->DoubleValue();
		coords.push_back(x);
		coords.push_back(y);
		pPoint = pPoint->NextSiblingElement("ponto");
	}
	glGenBuffers(1, vboPointer);
	glBindBuffer(GL_ARRAY_BUFFER, vboPointer[0]);
	glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(float), coords.data(), GL_STATIC_DRAW);
}


void ModelTexture::_draw()
{
	glBindTexture(GL_TEXTURE_2D, getImg());
	glBindBuffer(GL_ARRAY_BUFFER, vboPointer);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
