#include "Group.h"

Group::Group(XMLElement* xml_elem) {
	_xml_elem = xml_elem;
	_init();
}

void Group::_init() {
	add_models();
}

void Group::_draw() {
	_model._draw();
}

void Group::add_models() {
	XMLElement* pModels = _xml_elem->FirstChildElement("models");
	if (pModels == nullptr) {
		cout << "Invalid Models XML Element";
		throw 0x1;
	}
	_model = Models(pModels);
}