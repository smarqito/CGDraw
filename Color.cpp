#include "Color.h"

Color::Color()
{
}

Color::Color(XMLElement* xml)
{
	XMLElement* pDiffuse;
	XMLElement* pAmbient;
	XMLElement* pSpecular;
	XMLElement* pEmissive;
	XMLElement* valueShine;

	if((pDiffuse = xml->FirstChildElement("diffuse")) != nullptr) {
		float r = pDiffuse->FindAttribute("R")->FloatValue();
		float g = pDiffuse->FindAttribute("G")->FloatValue();
		float b = pDiffuse->FindAttribute("B")->FloatValue();
		setDiffuse(r, g, b);
	}

	if ((pAmbient = xml->FirstChildElement("ambient")) != nullptr) {
		float r = pAmbient->FindAttribute("R")->FloatValue();
		float g = pAmbient->FindAttribute("G")->FloatValue();
		float b = pAmbient->FindAttribute("B")->FloatValue();
		setAmbient(r, g, b);
	}

	if ((pSpecular = xml->FirstChildElement("specular")) != nullptr) {
		float r = pSpecular->FindAttribute("R")->FloatValue();
		float g = pSpecular->FindAttribute("G")->FloatValue();
		float b = pSpecular->FindAttribute("B")->FloatValue();
		setSpecular(r, g, b);
	}

	if ((pEmissive = xml->FirstChildElement("emissive")) != nullptr) {
		float r = pEmissive->FindAttribute("R")->FloatValue();
		float g = pEmissive->FindAttribute("G")->FloatValue();
		float b = pEmissive->FindAttribute("B")->FloatValue();
		setEmissive(r, g, b);
	}

	if ((valueShine = xml->FirstChildElement("shininess")) != nullptr) {
		float value = valueShine->FindAttribute("value")->FloatValue();
		setShininess(value);
	}
}

void Color::_draw()
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffuse());
	glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbient());
	glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecular());
	glMaterialfv(GL_FRONT, GL_EMISSION, getEmissive());
	glMaterialf(GL_FRONT, GL_SHININESS, getShininess());
}

float* Color::getDiffuse()
{
	return _diffuse;
}

float* Color::getAmbient()
{
	return _ambient;
}

float* Color::getSpecular()
{
	return _specular;
}

float* Color::getEmissive()
{
	return _emissive;
}

float Color::getShininess()
{
	return _shininess;
}

void Color::setDiffuse(float r, float g, float b)
{	
	_diffuse[0] = r;
	_diffuse[1] = g;
	_diffuse[2] = b;
}

void Color::setAmbient(float r, float g, float b)
{
	_ambient[0] = r;
	_ambient[1] = g;
	_ambient[2] = b;
}

void Color::setSpecular(float r, float g, float b)
{
	_specular[0] = r;
	_specular[1] = g;
	_specular[2] = b;
}

void Color::setEmissive(float r, float g, float b)
{
	_emissive[0] = r;
	_emissive[1] = g;
	_emissive[2] = b;
}

void Color::setShininess(float s)
{
	_shininess = s;
}
