#pragma once

#include "Camera.h"
#include "Lights.h"
#include "Groups.h"
#include "Group.h"
#include <GL/gl.h>

using namespace std;

class World
{
	//Camara settings --
	Camera camera;
	// lights settings
	Lights lights;
	// group --
	/// transform
	/// models }}}
	//// model }}}
	///// file * points }}}
	///// texture
	///// color
	////// diffuse | ambient | specular | emissive | shininess
	Groups groups;
public:
	World();

	void setCamera(float xPosition, float yPosition, float zPosition, float xLookAt, float yLookAt, float zLookAt, float xUp, float yUp, float zUp, float fov, float near, float far) {
		this->camera = Camera(xPosition, yPosition, zPosition, xLookAt, yLookAt, zLookAt, xUp, yUp, zUp, fov, near, far);
	}
	Camera getCamera() {
		return camera;
	}
	Groups getGroups() {
		return groups;
	}

	// lights

	//groups
	void addGroup(); // transform | models | transforms + models

	bool addModel(GLenum type, int size, char* path);

};