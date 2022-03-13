#pragma once

class Groups {

private:
	std::vector<Group> _groups;
	XMLElement* xml_elem;

public:
	Groups(XMLNode* xml_node);

	void _init();

	void _draw();
};
