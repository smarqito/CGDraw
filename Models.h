#pragma once
#ifndef MODELS_H
#define MODELS_H

#include "Model.h"
#include <vector>
#include <tinyxml2.h>

using namespace tinyxml2;

using namespace std;

class Models {

private:
	vector<Model> _models;
	XMLElement* _xml_elem;

public:
	Models();
	Models(XMLElement* xml_elem);

	void _init();

	Model get_model(int i);

	void _draw();
};
#endif // !MODELS_H

