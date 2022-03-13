#pragma once

class Groups {

private:
	vector<Group> _groups;
	XMLElement* xml_elem;

public:
	Groups(XMLNode* xml_node);

	void _init();

	void _draw() {
		for (int i = 0; i < _groups.size(); i++) {
			_groups[i]._draw();
		}
	}
};
