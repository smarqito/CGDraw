#include "Light.h"
#include "Point.h"
#ifndef _GL_INCLUDE
#define _GL_INCLUDE
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#endif // !_GL_INCLUDE
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

class PointLight : public Light {
private:
	float _point[4];
public:
	PointLight(int light_no , XMLElement* xmlElem);
	void _draw();
};

#endif
