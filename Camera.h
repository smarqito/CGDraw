#pragma once
class Camera {

private:
	point position;
	point lookat;
	point up;
	perspective projection;

public:
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

	point get_camera_projection();

	void _draw();
};
