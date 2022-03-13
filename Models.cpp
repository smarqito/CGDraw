#include "Models.h"

Models::Models(XMLElement* xml_elem) {
	_xml_elem = xml_elem;
	_init();
}

void Models::_init() {
	for (; _xml_elem != NULL; _xml_elem = _xml_elem->NextSiblingElement()) {
		_models.push_back(Model(_xml_elem));
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