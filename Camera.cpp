#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(XMLElement* xmlElement) {
	_xmlElement = xmlElement;
	_init();
}

Camera::Camera(point pos, point lookat, point up, perspective perspective) {
	set_camera(pos, lookat, up, perspective);
}

void Camera::_init() {
	XMLElement* pPosition = _xmlElement->FirstChildElement("position");
	_position.x = pPosition->FindAttribute("x")->FloatValue();
	_position.y = pPosition->FindAttribute("y")->FloatValue();
	_position.z = pPosition->FindAttribute("z")->FloatValue();
	XMLElement* pLookAt = _xmlElement->FirstChildElement("lookAt");
	_lookat.x = pLookAt->FindAttribute("x")->FloatValue();
	_lookat.y = pLookAt->FindAttribute("y")->FloatValue();
	_lookat.z = pLookAt->FindAttribute("z")->FloatValue();
	XMLElement* pUp = _xmlElement->FirstChildElement("up");
	_up.x = pUp->FindAttribute("x")->FloatValue();
	_up.y = pUp->FindAttribute("y")->FloatValue();
	_up.z = pUp->FindAttribute("z")->FloatValue();
	XMLElement* pProjection = _xmlElement->FirstChildElement("projection");
	_projection.fov = pProjection->FindAttribute("fov")->FloatValue();
	_projection.near = pProjection->FindAttribute("near")->FloatValue();
	_projection.far = pProjection->FindAttribute("far")->FloatValue();
}

void Camera::set_camera(point pos, point lookat, point up, perspective perspective) {
	set_camera_pos(pos);
	set_camera_lookat(lookat);
	set_camera_up(up);
	set_camera_projection(perspective);
}

void Camera::set_camera_pos(point pos) {
	_position.x = pos.x;
	_position.y = pos.y;
	_position.z = pos.z;
}

void Camera::set_camera_lookat(point lookat) {
	_lookat.x = lookat.x;
	_lookat.y = lookat.y;
	_lookat.z = lookat.z;
}

void Camera::set_camera_up(point up) {
	_up.x = up.x;
	_up.y = up.y;
	_up.z = up.z;
}

void Camera::set_camera_projection(perspective perp) {
	_projection.fov = perp.fov;
	_projection.near = perp.near;
	_projection.far = perp.far;
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

void Camera::_draw_projection(double ratio) {
	gluPerspective(_projection.fov, ratio, _projection.near, _projection.far);
}

void Camera::_draw_lookAt(){
	gluLookAt(_position.x, _position.y, _position.z,
		_lookat.x, _lookat.y, _lookat.z,
		_up.x, _up.y, _up.z);
}