#include "Transform.h"
#include <math.h>

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
	_y_i.setPoint(0, 0);
	_y_i.setPoint(1, 1);
	_y_i.setPoint(2, 0);
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
		t.last_time = 0.0;
		t.curve = false;
		nome = elem->Value();
		if (strcmp(nome, "translate") == 0 && strcmp(elem->FirstAttribute()->Name(), "time") == 0) {

			t.time = elem->FindAttribute("time")->FloatValue();
			t.align = elem->FindAttribute("align")->BoolValue();
			t.translate_rate = 0.0;
			t.curve = true;
			XMLElement* points = elem->FirstChildElement();
			while (points != nullptr) {
				Point p;
				p.x = points->FindAttribute("x")->FloatValue();
				p.y = points->FindAttribute("y")->FloatValue();
				p.z = points->FindAttribute("z")->FloatValue();
				t.points.push_back(p);
				points = points->NextSiblingElement();
			}
		}
		else {

			t.p.x = elem->FindAttribute("x")->FloatValue();
			t.p.y = elem->FindAttribute("y")->FloatValue();
			t.p.z = elem->FindAttribute("z")->FloatValue();

			if (strcmp(nome, "rotate") == 0) {
				if (strcmp(elem->FirstAttribute()->Name(), "angle") == 0) {
					t.a = elem->FindAttribute("angle")->FloatValue();
				}
				else {
					t.time = elem->FindAttribute("time")->FloatValue();
					t.rotate_rate = 0.0;
					t.curve = true;
				}
			}
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
			if (_transformations[i].curve) {
				Curve curve(CATMULL);
				curve.addControlPoint(_transformations[i].points);
				Matrix pos(1, 3), deriv(1,3);

				curve.getPoint(_transformations[i].translate_rate, pos, deriv);

				glTranslatef(pos.getPoint(0), pos.getPoint(1), pos.getPoint(2));

				if (_transformations[i].align) {
					Matrix m(4, 4);
					Matrix z(1, 3);
					
					deriv.cross(_y_i, z);
					z.cross(deriv, _y_i);

					deriv.normalize_lines();
					_y_i.normalize_lines();
					z.normalize_lines();

					RotMatrix rot_matrix(deriv, _y_i, z);

					glMultMatrixf(rot_matrix.to_array());
				}

				float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
				_transformations[i].translate_rate += (time - _transformations[i].last_time) / float(_transformations[i].time); //calculte the new translate_rate
				_transformations[i].translate_rate -= 1 * floor(_transformations[i].translate_rate / 1); //normalize between 0 - 1 
				_transformations[i].last_time = time; //update the last time
			}
			else {
				glTranslatef(_transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
			}
			break;
		case ROTATE:
			if (_transformations[i].curve) {
				float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
				_transformations[i].rotate_rate += (time - _transformations[i].last_time) / float(_transformations[i].time);//calculte the new rotate_rate
				_transformations[i].rotate_rate -= 1 * floor(_transformations[i].rotate_rate / 1); //normalize between 0 - 1 
				float angle = 360 * _transformations[i].rotate_rate; //calculate the new angle
				glRotatef(angle, _transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
				_transformations[i].last_time = time;
			}
			else {
				glRotatef(_transformations[i].a, _transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
			}
			break;
		case SCALE:
			glScalef(_transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
			break;
		default:
			break;
		}
	}
}
