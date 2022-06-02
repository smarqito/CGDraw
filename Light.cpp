#include "Light.h"

Light::Light(int light_no)
{
	_light_no = light_no;
}

void Light::setLightNo(int number)
{
	_light_no = number;
}

int Light::getLightNo()
{
	return _light_no;
}
