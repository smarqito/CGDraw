#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#ifndef CAMERA_H
#define CAAMERA_H

#include "cartesian/cartesian.h"
#include <tinyxml2.h>

using namespace tinyxml2;

enum CAMenum
{
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

class Camera {

private:
	point _position;
	point _lookat;
	polar _lookat_p;
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
	void set_camera_pos(double x, double y, double z);

	void set_camera_lookat(point lookat);
	void set_camera_lookat(double x, double y, double z);

	void set_camera_up(point up);
	void set_camera_up(double x, double y, double z);

	void set_camera_projection(perspective perp);
	void set_camera_projection(double fov, double near, double far);

	point get_camera_pos();

	point get_camera_lookat();

	point get_camera_up();

	perspective get_camera_projection();

	void move_camera(CAMenum t);
	void move_lookat(double alpha, double beta);

	void _draw_projection(double ratio);

	void _draw_lookAt();
};
#endif // !CAMERA_H

