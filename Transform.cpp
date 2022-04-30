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
}

Transform::Transform(XMLElement* transform_elem)
{
	_transform_elem = transform_elem;
	yAnt[0] = 0;
	yAnt[1] = 1;
	yAnt[2] = 0;
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

void buildRotMatrix(float* x, float* y, float* z, float* m) {

	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}

void multMatrixVector(double* m, double* v, double* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float* pos, float* deriv) {

	// catmull-rom matrix
	double m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };

	double P[3][4] = { {p0.x, p1.x, p2.x, p3.x},
					{p0.y, p1.y, p2.y, p3.y},
					{p0.z, p1.z, p2.z, p3.z} };
	for (int i = 0; i < 3; i++) {
		double a[4];
		double Paux[4] = { P[i][0], P[i][1], P[i][2], P[i][3] };
		// Compute A = M * P
		multMatrixVector(m[0], Paux, a);
		// Compute pos = T * A
		double T[4] = { pow(t,3), pow(t,2), t, 1 };
		pos[i] = T[0] * a[0] + T[1] * a[1] + T[2] * a[2] + T[3] * a[3];
		// compute deriv = T' * A
		double Tlinha[4] = { 3 * pow(t,2), 2 * t, 1, 0 };
		deriv[i] = Tlinha[0] * a[0] + Tlinha[1] * a[1] + Tlinha[2] * a[2] + Tlinha[3] * a[3];
	}

}


// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, vector<Point> points) {
	int POINT_COUNT = points.size();
	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
	indices[1] = (indices[0] + 1) % POINT_COUNT;
	indices[2] = (indices[1] + 1) % POINT_COUNT;
	indices[3] = (indices[2] + 1) % POINT_COUNT;

	getCatmullRomPoint(t, points[indices[0]], points[indices[1]], points[indices[2]], points[indices[3]], pos, deriv);
}

void Transform::_draw()
{
	for (int i = 0; i < _transformations.size(); i++)
	{
		switch (_transformations[i].t)
		{
		case TRANSLATE:
			if (_transformations[i].curve) {
				//renderCatmullRomCurve(_transformations[i].points);
				float pos[3];
				float deriv[3];
				getGlobalCatmullRomPoint(_transformations[i].translate_rate, pos, deriv, _transformations[i].points);
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
