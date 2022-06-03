#pragma once
#include "Group.h"
#ifndef GROUPS_H
#define GROUPS_H

#include <tinyxml2.h>
using namespace tinyxml2;

class Groups {

private:
	std::vector<Group> _groups;
	XMLElement* _xml_group; // first group elem

public:
	Groups();
	Groups(XMLElement* xml_group);

	void _init();
	/*
	* Draw the groups
	*/
	void _draw();

	void add_group(XMLElement* elem);
};

#endif // !GROUPS_H