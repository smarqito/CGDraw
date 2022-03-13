#include "World.h"

World::World(const char* xmlpath) {
	path = strdup(xmlpath);
	_init();

}

void World::_init() {
	XMLDocument doc;
	doc.LoadFile(path);
	XMLNode* pRootElement = doc.FirstChild();

	if (pRootElement == nullptr) {
		cout << "Invalid World Root XML Element";
		throw 0x1;
	}

	XMLElement* pCamera = pRootElement->FirstChildElement("camera");
	if (pCamera == nullptr) {
		cout << "Invalid Camara XML Element";
		throw 0x1;
	}

	_camera = Camera(pCamera);
	XMLElement* pGroup = pRootElement->FirstChildElement("group");
	if (pGroup == nullptr) {
		cout << "Invalid Group XML Element";
		throw 0x1;
	}

	_groups = Groups(pGroup);
}

void World::_draw()
{
	_camera._draw();
	_groups._draw();
}

void World::_draw_projection(double ratio) {
	_camera._draw_projection(ratio);
}

void World::_draw_lookAt() {
	_camera._draw_lookAt();
}

void World::set_camera_pos(point pos) {
	_camera.set_camera_pos(pos);
}

void World::set_camera_lookat(point lookat) {
	_camera.set_camera_lookat(lookat);
}

void World::set_camera_up(point up) {
	_camera.set_camera_up(up);
}

void World::set_camera_persp(perspective perp) {
	_camera.set_camera_projection(perp);
}

