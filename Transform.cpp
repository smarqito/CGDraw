#include "Transform.h"

type from_name(const char* name) {
	if (strcmp(name, "translate") == 0) {
		return TRANSLATE;
	}
	else if (strcmp(name, "rotate") == 0) {
		return ROTATE;
	}
	else if (strcmp(name, "scale") == 0) {
		return SCALE;
	}
	throw 0x01;
}

Transform::Transform()
{
}

Transform::Transform(XMLElement* transform_elem)
{
	_transform_elem = transform_elem;
	_init();
}

void Transform::_init()
{
	const char* nome;
	XMLElement* elem = _transform_elem->FirstChildElement();
	while (elem != nullptr) {
		transformation t;
		nome = elem->Value();
		t.p.x = elem->FindAttribute("x")->FloatValue();
		t.p.y = elem->FindAttribute("y")->FloatValue();
		t.p.z = elem->FindAttribute("z")->FloatValue();

		if (strcmp(nome, "rotate") == 0) {
			t.a = elem->FindAttribute("angle")->FloatValue();
		}
		t.t = from_name(nome);
		_transformations.push_back(t);
		elem = elem->NextSiblingElement();
	}
}

void Transform::_draw()
{
	for (int i = 0; i < _transformations.size(); i++)
	{
		switch (_transformations[i].t)
		{
		case TRANSLATE:
			glTranslatef(_transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
			break;
		case ROTATE:
			glRotatef(_transformations[i].a, _transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
			break;
		case SCALE:
			glScalef(_transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
			break;
		default:
			break;
		}
	}
}
