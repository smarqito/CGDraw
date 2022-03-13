#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "cartesian/cartesian.h"
#include <tinyxml2.h>

using namespace tinyxml2;

class Camera {

private:
	point _position;
	point _lookat;
	point _up;
	perspective _projection;
	XMLElement* _xmlElement;

public:
	Camera();

	Camera(XMLElement* xmlElement);

	Camera(point pos, point lookat, point up, perspective perspective);

	void _init();

	void set_camera(point pos, point lookat, point up, perspective perspective);

	void set_camera_pos(point pos);

	void set_camera_lookat(point lookat);

	void set_camera_up(point up);

	void set_camera_projection(perspective perp);

	point get_camera_pos();

	point get_camera_lookat();

	point get_camera_up();

	perspective get_camera_projection();

	void _draw_projection(double ratio);

	void _draw_lookAt();
};
