#include "Models.h"

Models::Models()
{
}

Models::Models(XMLElement* xml_elem) {
	_xml_elem = xml_elem;
	_init();
}

void Models::_init() {
	XMLElement* it = _xml_elem->FirstChildElement("model");
	while (it != NULL) {
		_models.push_back(Model(it));
		it = it->NextSiblingElement("model");
	}
}

Model Models::get_model(int i) {
	return _models[i];
}

void Models::_draw() {
	for (int i = 0; i < _models.size(); i++) {
		_models[i]._draw();
	}
}