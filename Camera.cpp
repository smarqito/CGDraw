#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
Camera::Camera() {
	_scale = 1;
}

Camera::Camera(XMLElement* xmlElement) {
	_xmlElement = xmlElement;
	_scale = 1;
	_init();
}

Camera::Camera(point pos, point lookat, point up, perspective perspective) {
	_scale = 1;
	set_camera(pos, lookat, up, perspective);
}

void Camera::_init() {
	XMLElement* pPosition = _xmlElement->FirstChildElement("position");
	double x = pPosition->FindAttribute("x")->DoubleValue();
	double y = pPosition->FindAttribute("y")->DoubleValue();
	double z = pPosition->FindAttribute("z")->DoubleValue();
	set_camera_pos(x, y, z);

	XMLElement* pLookAt = _xmlElement->FirstChildElement("lookAt");
	x = pLookAt->FindAttribute("x")->DoubleValue();
	y = pLookAt->FindAttribute("y")->DoubleValue();
	z = pLookAt->FindAttribute("z")->DoubleValue();
	set_camera_lookat(x, y, z);

	XMLElement* pUp = _xmlElement->FirstChildElement("up");
	x = pUp->FindAttribute("x")->DoubleValue();
	y = pUp->FindAttribute("y")->DoubleValue();
	z = pUp->FindAttribute("z")->DoubleValue();
	set_camera_up(x, y, z);

	XMLElement* pProjection = _xmlElement->FirstChildElement("projection");
	x = pProjection->FindAttribute("fov")->DoubleValue();
	y = pProjection->FindAttribute("near")->DoubleValue();
	z = pProjection->FindAttribute("far")->DoubleValue();
	set_camera_projection(x, y, z);
}

void Camera::set_camera(point pos, point lookat, point up, perspective perspective) {
	set_camera_pos(pos);
	set_camera_lookat(lookat);
	set_camera_up(up);
	set_camera_projection(perspective);
}

void Camera::set_camera_pos(point pos) {
	set_camera_pos(pos.x, pos.y, pos.z);
}

void Camera::set_camera_pos(double x, double y, double z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

void Camera::set_camera_lookat(point lookat) {
	set_camera_lookat(lookat.x, lookat.y, lookat.z);
}

void Camera::set_camera_lookat(double x, double y, double z) {
	// A
	_lookat.x = x;
	_lookat.y = y;
	_lookat.z = z;
	sub_points(&_lookat, &_position);
	double r = sqrt(_lookat.x * _lookat.x + _lookat.y * _lookat.y + _lookat.z * _lookat.z);
	_lookat.x /= r;
	_lookat.y /= r;
	_lookat.z /= r;


	polar p = cart_to_polar(_lookat.x, _lookat.y, _lookat.z);
	_lookat_p.r = p.r;
	_lookat_p.a = p.a;
	_lookat_p.b = p.b;
}

void Camera::set_camera_up(point up) {
	set_camera_up(up.x, up.y, up.z);
}

void Camera::set_camera_up(double x, double y, double z) {
	_up.x = x;
	_up.y = y;
	_up.z = z;
}

void Camera::set_camera_projection(perspective perp) {
	set_camera_projection(perp.fov, perp.nr, perp.fr);
}

void Camera::set_camera_projection(double fov, double nr, double fr) {
	_projection.fov = fov;
	_projection.nr = nr;
	_projection.fr = fr;
}

point Camera::get_camera_pos() {
	return _position;
}

point Camera::get_camera_lookat() {
	return _lookat;
}

point Camera::get_camera_up() {
	return _up;
}

perspective Camera::get_camera_projection() {
	return _projection;
}

void Camera::change_scale(float newScale)
{
	_scale = max(_scale + newScale, 0.1f);
}

// TODO
void Camera::move_camera(CAMenum t)
{
	point p;
	switch (t)
	{
	case LEFT:
		p = polartocart(_scale, _lookat_p.a + (M_PI / 2), 0);
		sum_points(&_position, &p);
		break;
	case RIGHT:
		p = polartocart(_scale, _lookat_p.a - (M_PI / 2), 0);
		sum_points(&_position, &p);
		break;
	case FRONT:
		p = scale_factor(_lookat, _scale);
		sum_points(&_position, &p);
		break;
	case BACK:
		p = scale_factor(_lookat, _scale);
		sub_points(&_position, &p);
		break;
	default:
		break;
	}
}

void Camera::move_lookat(double alpha, double beta)
{

	_lookat_p.a += alpha;
	//_lookat_p.b += beta;
	_lookat_p.b = fmax(fmin(_lookat_p.b + beta, 1.5f), -1.5f);
	point p = polartocart(_lookat_p);
	_lookat.x = p.x;
	_lookat.y = p.y;
	_lookat.z = p.z;
}

void Camera::_draw_projection(double ratio) {
	gluPerspective(_projection.fov, ratio, _projection.nr, _projection.fr);
}

void Camera::_draw_lookAt() {
	gluLookAt(_position.x, _position.y, _position.z,
		_position.x + _lookat.x, _position.y + _lookat.y, _position.z + _lookat.z,
		_up.x, _up.y, _up.z);
}