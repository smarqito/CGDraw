#pragma once

#include "Camera.h"
#include "Lights.h"
#include "Groups.h"
#include "Group.h"
#include <GL/gl.h>

using namespace std;

class World {

private:
	Camera camera;
	Groups groups;
	Lights lights;
	string path;

public:
	World(string xmlpath);

	void _init();

	void _draw() {
		groups._draw();
	}

	void set_camera_pos(point pos);

	void set_camera_lookat(point lookat);

	void set_camera_up(point up);

	void set_camera_persp(perspective perp);
};

