#include "curves.h"

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

void getCatmullRomPoint(float t, point p0, point p1, point p2, point p3, float* pos, float* deriv) {

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
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, vector<point> points) {
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