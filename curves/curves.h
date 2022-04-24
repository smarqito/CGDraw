#include <vector>
#include <math.h>
#include "../cartesian/cartesian.h"

using namespace std;

void buildRotMatrix(float* x, float* y, float* z, float* m);
void cross(float* a, float* b, float* res);
void normalize(float* a);
void multMatrixVector(double* m, double* v, double* res);
void getCatmullRomPoint(float t, point p0, point p1, point p2, point p3, float* pos, float* deriv);
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, vector<point> points);

