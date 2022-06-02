#include "Texture.h"
#include "Common.h"

GLuint Texture::loadTexture()
{
	unsigned int t;
	unsigned char* texData;
	unsigned int texID;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)tex_path.c_str());
	iw = ilGetInteger(IL_IMAGE_WIDTH);
	ih = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iw, ih, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

Texture::Texture()
{
}

Texture::Texture(XMLElement* xml_elem)
{
	string t = string(file_path);
	setPath(t + string(xml_elem->FindAttribute("file")->Value()));
	img = loadTexture();
}

string Texture::getPath()
{
	return tex_path;
}

int Texture::getImg()
{
	return img;
}

void Texture::draw()
{
}

void Texture::setPath(string path)
{
	tex_path = path;
}
