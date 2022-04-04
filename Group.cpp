#include "Group.h"

Group::Group(XMLElement* xml_elem) {
	_xml_elem = xml_elem;
	_init();
}

void Group::_init() {
	add_transform();
	add_models();
	add_groups();
}

void Group::_draw() {
	glPushMatrix();
	_transform._draw();
	// add nested group
	_model._draw();
	for (int i = 0; i < _groups.size(); i++)
	{
		_groups[i]._draw();
	}
	glPopMatrix();
}

void Group::add_transform() {
	XMLElement* pTransform = _xml_elem->FirstChildElement("transform");
	if (pTransform != nullptr) { // to remove * might not transform
		_transform = Transform(pTransform);
	}
}

void Group::add_groups() {
	XMLElement* pGroup = _xml_elem->FirstChildElement("group");
	while (pGroup != nullptr) {
		_groups.push_back(Group(pGroup));
		pGroup = pGroup->NextSiblingElement("group");
	}
}

void Group::add_models() {
	XMLElement* pModels = _xml_elem->FirstChildElement("models");
	if (pModels != nullptr) {
		_model = Models(pModels);
	}
}