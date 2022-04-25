#include "World.h"
#include <regex>
#include <string>
#include "Common.h"
using namespace std;

string file_path;


World::World()
{
}

World::World(const char* xmlpath) {
	_path = strdup(xmlpath);
	_init();

}

void World::_init() {
	XMLDocument doc;
	doc.LoadFile(_path);
	set_root_path();
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
	_groups._draw();
}

string World::set_root_path()
{
	regex regexp(R"((.*(/|\\))?.*.xml)");
	smatch m;
	string t = string(_path);
	regex_search(t, m, regexp);
	cout << m[1];
	file_path = m[1];
	return m[1];
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
void World::set_camera_pos(double x, double y, double z) {
	_camera.set_camera_pos(x, y, z);
}

void World::move_camera_pos(CAMenum t) {
	_camera.move_camera(t);
}

void World::move_lookat(double alpha, double beta) {
	_camera.move_lookat(alpha, beta);
}

void World::set_camera_lookat(point lookat) {
	_camera.set_camera_lookat(lookat);
}
void World::set_camera_lookat(double x, double y, double z) {
	_camera.set_camera_lookat(x, y, z);
}

void World::change_scale(float newScale)
{
	_camera.change_scale(newScale);
}

void World::set_camera_up(point up) {
	_camera.set_camera_up(up);
}

void World::set_camera_persp(perspective perp) {
	_camera.set_camera_projection(perp);
}

