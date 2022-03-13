#pragma once
#include "Model.h"
#include <vector>

using namespace std;

class Models {

private:
	vector<Model> models;
	XMLElement* xml_elem;

public:
	Models(XMLElement* xml_elem);

	void _init();

	Model get_model();

	Model get_model(int i);

	void _draw(){
		for (int i = 0; i < models.size(); i++) {
			models[i]._draw();
		}
	}
};
