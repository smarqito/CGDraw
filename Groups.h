#pragma once
#ifndef GROUPS_H
#define GROUPS_H
#endif // !GROUPS_H

#include <tinyxml2.h>
#include "Group.h"
using namespace tinyxml2;

class Groups {

private:
	vector<Group> _groups;
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
