#pragma once

#include "Camera.h"
#include "Lights.h"
#include "Groups.h"
#include "Group.h"
#include <GL/gl.h>
#include <tinyxml2.h>
#include <iostream>

using namespace std;
using namespace tinyxml2;

class World {

private:
	Camera _camera;
	Groups _groups;
	Lights _lights;
	char* path;

public:
	
	/*
	* Construtor vazio para a classe world
	* Recebe como par�metro o path para o ficheiro XML a ler
	* Inicia o processo de leitura do ficheiro
	*/
	World(const char* xmlpath);

	/*
	* Inicio do processo de leitura do ficheiro 
	* Passa � classe Camara e Groups os repetivos elementos XML a ler
	*/
	void _init();

	/*
	* Fun��o para iniciar o processo de desenho da figura geom�trica
	* Passa a responsabilidade para a classe camara e classe groups
	*/
	void _draw();

	// N�o h� nenhuma restri��o para a ratio recebido 
	void _draw_projection(double ratio);

	void _draw_lookAt();

	// N�o h� nenhuma restri��o para a posi��o a receber 
	void set_camera_pos(point pos);

	// N�o h� nenhuma restri��o para o lookaAt da c�mera
	void set_camera_lookat(point lookat);

	// N�o h� nenhuma restri��o para o up point da c�mera
	void set_camera_up(point up);

	// N�o h� nenhuma restri��o para a projection da c�mera
	void set_camera_persp(perspective perp);
};

