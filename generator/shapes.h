#include <tuple>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../cartesian/cartesian.h"
#include "../cartesian/Curve.h"
#include "../cartesian/BezierTriangles.h"
#ifndef SHAPES_DRAW
#pragma once


/*
* Função que cria um array de pontos para construir o plano
*
*/
std::tuple<t_points, t_points, std::vector<float>> create_plane(float length, int divisions);

/*
* Função que cria um array de pontos para construir uma caixa
*/
std::tuple<t_points, t_points, std::vector<float>> create_box(float units, int divisions);

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
t_points create_bezier(std::vector<std::vector<int>> patches, std::vector<Point> points, int level);

t_points create_sphere(int radius, int slices, int stacks, Point offset);

t_points create_asteroids(double distMin, double distMax, int maxSize, int slices, int stacks, double alphaMax, double betaMax, int numAsteroids);
#endif // !SHAPES_DRAW
