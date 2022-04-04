#include "Groups.h"

Groups::Groups()
{
}

Groups::Groups(XMLElement* xml_group) {
	_xml_group = xml_group;
	_init();
}

void Groups::_init() {
	XMLElement* group = _xml_group; // don't loose the reference to first elem group
	while (group != NULL) {

		add_group(group);
		group = group->NextSiblingElement("group");
	}
}

void Groups::_draw() {
	for (int i = 0; i < _groups.size(); i++) {
		_groups[i]._draw();
	}
}

void Groups::add_group(XMLElement* elem)
{
	_groups.push_back(Group(elem));
}
