#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include <tinyxml2.h>
#include <string>
#include <GL/glut.h>
#include <GL/glew.h>
#include <IL/il.h>

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
	void draw();
};
#endif