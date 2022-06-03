#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include <tinyxml2.h>
#include <string>
#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE
using namespace tinyxml2;

class Texture
{
private:
	int img;
	unsigned int iw;
	unsigned int ih;
	std::string tex_path;

	GLuint loadTexture();
public:
	Texture();
	Texture(XMLElement* xml_elem);
	void setPath(std::string path);
	std::string getPath();
	int getImg();
	virtual void _draw() = 0;
};
#endif