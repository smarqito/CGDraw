#pragma once
#include <list>
#include "Model.h"

using namespace std;

class Models
{
	list<Model> models;

public:

	list<Model> getModels() {
		return models;
	}

	void addModel(GLenum type, int size, const char* filename) {
		Model m = Model(type, size, filename);
		models.push_back(m);
	}
};
