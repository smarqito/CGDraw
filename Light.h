#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <Point.h>
#include <tinyxml2.h>

using namespace tinyxml2;

class Light
{
public:
	int _light_no;
	Light(int light_no);
	virtual void _draw(){ };
	void setLightNo(int number);
	int getLightNo();

};

#endif // !LIGHT_H