#include <tuple>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../cartesian/cartesian.h"
#include "../cartesian/Curve.h"
#include "../cartesian/BezierTriangles.h"
#ifndef SHAPES_DRAW
#pragma once

using namespace std;


/*
* Função que cria um array de pontos para construir o plano
*
*/
t_points create_plane(float length, int divisions);

/*
* Função que cria um array de pontos para construir uma caixa
*/
t_points create_box(float units, int divisions);

/*
* Função que cria um array de pontos para construir o cone
*/
t_points create_cone(float radius, float height, int slices, int stacks);

/*
* Função que cria um array de pontos para construir a esfera
*/
t_points create_sphere(int radius, int slices, int stacks);

/*
* Função que cria um array de pontos para construir o cilindro
*/
t_points create_cylinder(int radius, int height, int slices, int stacks);

t_points create_torus(float radius, float size, int slices, int stack);

/*
Create a vector of list of points that can be drawn with line loop
*/
t_points create_bezier(vector<vector<int>> patches, vector<Point> points, int level);
#endif // !SHAPES_DRAW
