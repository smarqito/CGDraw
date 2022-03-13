#pragma once
#include <list>
#include "Model.h"

using namespace std;

class Models {

private:
	std::vector<Model> models;
	XMLElement* xml_elem;

public:
	Models(XMLElement* xml_elem);

	void _init();

	Model get_model();

	Model get_model(int i);

	void _draw();
};
