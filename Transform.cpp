#include "Transform.h"

float yAnt[3] = { 0, 1, 0 };

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
		t.curve = false;
		nome = elem->Value();
		if (strcmp(nome, "translate") == 0 && strcmp(elem->FirstAttribute()->Name(), "time") == 0) {

			t.time = elem->FindAttribute("time")->FloatValue();
			t.align = elem->FindAttribute("align")->BoolValue();
			t.curve = true;
			XMLElement* points = elem->FirstChildElement();
			while (points != nullptr) {
				point p;
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
				static float gt = 0;
				float pos[3];
				float deriv[3];
				getGlobalCatmullRomPoint(gt, pos, deriv, _transformations[i].points);
				glTranslatef(pos[0], pos[1], pos[2]);
				if (_transformations[i].align) {
					float m[4][4];
					float x[3] = { deriv[0], deriv[1], deriv[2] };
					float z[3];
					cross(x, yAnt, z);
					cross(z, x, yAnt);
					normalize(x);
					normalize(z);
					normalize(yAnt);

					buildRotMatrix(x, yAnt, z, m[0]);

					glMultMatrixf(m[0]);
				}
				int time = glutGet(GLUT_ELAPSED_TIME);
				gt += 0.001;
			}
			else {
				glTranslatef(_transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
			}
			break;
		case ROTATE:
			if (_transformations[i].curve) {
				static float rt = 0.0;
				
				int time = glutGet(GLUT_ELAPSED_TIME); //rever esta parte
				float angle = 360.0 / time;
				glRotatef(angle, _transformations[i].p.x, _transformations[i].p.y, _transformations[i].p.z);
				rt += angle;
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
