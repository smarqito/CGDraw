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
	_y_i.setPoint(1, 1); // y0 = (0 1 0)
}

void Transform::_init()
{
	const char* nome;
	XMLElement* elem = _transform_elem->FirstChildElement();
	while (elem != nullptr) {
		transformation t;
		//t.last_time = 0.0;
		//t.curve = false;
		nome = elem->Value();
		if (strcmp(nome, "translate") == 0 && elem->Attribute("time")) {
			// define is curve
			t.curve = true;

			//set curve type
			int curveType = elem->IntAttribute("curve", CATMULL); // default is bezier
			if (curveType == -1) {
				// CARREGAR VALOR XML
			}
			else {
				t._t_curve = TranslateCurve((DefMat)curveType);
			}

			// set time control and align
			t._time.setTime(elem->FindAttribute("time")->FloatValue());
			t._t_curve.setAlign(elem->BoolAttribute("align"));

			XMLElement* points = elem->FirstChildElement();
			vector<Point> c_points;

			while (points != nullptr) {
				Point p;
				p.x = points->FindAttribute("x")->FloatValue();
				p.y = points->FindAttribute("y")->FloatValue();
				p.z = points->FindAttribute("z")->FloatValue();
				c_points.push_back(p);
				points = points->NextSiblingElement();
			}
			t._t_curve.addControlPoint(c_points);
		}
		else {

			t.p.x = elem->FindAttribute("x")->FloatValue();
			t.p.y = elem->FindAttribute("y")->FloatValue();
			t.p.z = elem->FindAttribute("z")->FloatValue();

			if (strcmp(nome, "rotate") == 0) {
				if (elem->Attribute("angle")) {
					t.a = elem->FloatAttribute("angle");
				}
				else {
					t._time.setTime(elem->FloatAttribute("time"));
					//t.rotate_rate = 0.0;
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
				
				_transformations[i]._t_curve._draw(_transformations[i]._time.getRate());
				_transformations[i]._time.updateRate();
			}
			else {
				glTranslatef(_transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
			}
			break;
		case ROTATE:
			if (_transformations[i].curve) {
				_transformations[i]._time.updateRate();
				float angle = 360 * _transformations[i]._time.getRate(); //calculate the new angle
				glRotatef(angle, _transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
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
