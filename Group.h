#pragma once
#include "Models.h"


class Group {

private:
	Models _model;
	XMLElement* xml_elem;

public:
	Group(XMLElement* xml_elem);

	void _init();

	void _draw() {
		_model._draw();
	}

	void add_models();
};
