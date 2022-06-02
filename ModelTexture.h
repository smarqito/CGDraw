#pragma once
#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H
#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE
#include <tinyxml2.h>
#include <vector>
#include <Texture.h>

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

#endif
