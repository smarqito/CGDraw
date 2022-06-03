#include "ModelTexture.h"


ModelTexture::ModelTexture()
{
}

ModelTexture::ModelTexture(XMLElement* pontos, XMLElement* texture) : Texture(texture)
{
	std::vector<float> coords;
	vboPointer = (GLuint*)malloc(sizeof(GLuint));
	XMLElement* pPoint = pontos->FirstChildElement("point");

	double x, y;
	while (pPoint != NULL) {
		x = pPoint->FindAttribute("x")->DoubleValue();
		y = pPoint->FindAttribute("y")->DoubleValue();
		coords.push_back(x);
		coords.push_back(y);
		pPoint = pPoint->NextSiblingElement("point");
	}
	glGenBuffers(1, vboPointer);
	glBindBuffer(GL_ARRAY_BUFFER, vboPointer[0]);
	glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(float), coords.data(), GL_STATIC_DRAW);
}


void ModelTexture::_draw()
{
	glBindTexture(GL_TEXTURE_2D, getImg());
	glBindBuffer(GL_ARRAY_BUFFER, vboPointer[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);
	
}
