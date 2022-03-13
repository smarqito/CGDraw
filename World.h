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
	* Recebe como parâmetro o path para o ficheiro XML a ler
	* Inicia o processo de leitura do ficheiro
	*/
	World(const char* xmlpath);

	/*
	* Inicio do processo de leitura do ficheiro 
	* Passa à classe Camara e Groups os repetivos elementos XML a ler
	*/
	void _init();

	/*
	* Função para iniciar o processo de desenho da figura geométrica
	* Passa a responsabilidade para a classe camara e classe groups
	*/
	void _draw();

	// Não há nenhuma restrição para a ratio recebido 
	void _draw_projection(double ratio);

	void _draw_lookAt();

	// Não há nenhuma restrição para a posição a receber 
	void set_camera_pos(point pos);

	// Não há nenhuma restrição para o lookaAt da câmera
	void set_camera_lookat(point lookat);

	// Não há nenhuma restrição para o up point da câmera
	void set_camera_up(point up);

	// Não há nenhuma restrição para a projection da câmera
	void set_camera_persp(perspective perp);
};

