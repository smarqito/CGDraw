#include "Transform.h"
#include <GL/glut.h>

Transform::Transform(XMLElement* transform_elem)
{
	_transform_elem = transform_elem;
}

void Transform::_init()
{
	XMLElement* translate = _transform_elem->FirstChildElement("translate");
	if ((_t = translate != nullptr)) {
		_translate.x = translate->FindAttribute("x")->FloatValue();
		_translate.y = translate->FindAttribute("y")->FloatValue();
		_translate.z = translate->FindAttribute("z")->FloatValue();
	}
	XMLElement* rotate = _transform_elem->FirstChildElement("rotate");
	if ((_r = rotate != nullptr)) {
		_rotate_a = rotate->FindAttribute("angle")->FloatValue();
		_rotate_p.x = rotate->FindAttribute("x")->FloatValue();
		_rotate_p.y = rotate->FindAttribute("y")->FloatValue();
		_rotate_p.z = rotate->FindAttribute("z")->FloatValue();
	}

	XMLElement* scale = _transform_elem->FirstChildElement("scale");
	if ((_s = scale != nullptr)) {
		_scale.x = scale->FindAttribute("x")->FloatValue();
		_scale.y = scale->FindAttribute("y")->FloatValue();
		_scale.z = scale->FindAttribute("z")->FloatValue();
	}
}

void Transform::_draw()
{
	if (_t)
		glTranslatef(_translate.x, _translate.y, _translate.z);
	if (_r)
		glRotatef(_rotate_a, _rotate_p.x, _rotate_p.y, _rotate_p.z);
	if (_s)
		glScalef(_scale.x, _scale.y, _scale.z);
}
