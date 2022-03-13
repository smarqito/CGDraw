#pragma once

#include "Camera.h"
#include "Lights.h"
#include "Groups.h"
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

	void setCamera();
	Camera getCamera();

	// lights

	//groups
	void addGroup(); // transform | models | transforms + models

	bool addModel(GLenum type, int size, char* path);

};