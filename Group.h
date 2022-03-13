#pragma once
#include "Models.h"
#include <iostream>
#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

class Group {

private:
	Models _model;
	XMLElement* _xml_elem;

public:

	/*
	* Construtor para a classe Group
	* Recebe o elemento do grupo para manipular
	*/
	Group(XMLElement* xml_elem);

	/*
	* Inicia os models que se encontram no grupo
	*/
	void _init();

	/*
	* Passa a dependencia para a classe Models para desenhar as figuras geométricas
	*/
	void _draw();

	void add_models();
};
