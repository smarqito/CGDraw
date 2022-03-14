#pragma once
#ifndef WORLD_H
#define WORLD_H

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

public:
	char* _path;
	World();
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

	string set_root_path();

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

	//
	void set_camera_pos(double x, double y, double z);
	//
	void move_camera_pos(CAMenum m);
	void move_lookat(double alpha, double beta);
	// Não há nenhuma restrição para o lookaAt da câmera
	void set_camera_lookat(point lookat);

	void set_camera_lookat(double x, double y, double z);

	// Não há nenhuma restrição para o up point da câmera
	void set_camera_up(point up);

	// Não há nenhuma restrição para a projection da câmera
	void set_camera_persp(perspective perp);
};

#endif // !WORLD_H