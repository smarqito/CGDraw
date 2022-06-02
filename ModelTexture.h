#pragma once
#include <GL/glut.h>
#include <tinyxml2.h>
#include <vector>
#include <Texture.h>


using namespace std;
using namespace tinyxml2;

class ModelTexture : public Texture
{
private:
	GLuint *vboPointer;
public:
	ModelTexture();
	ModelTexture(XMLElement* pontos, XMLElement* texture);
	void _draw();
};
