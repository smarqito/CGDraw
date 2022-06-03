#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <Point.h>
#include <tinyxml2.h>

using namespace tinyxml2;


class Light
{
private:
	int _light_no;
public:
	Light(int light_no);
	virtual void _draw() = 0;
	void setLightNo(int number);
	int getLightNo();

};

#endif // !LIGHT_H