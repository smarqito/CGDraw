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
std::tuple<t_points, t_points, std::vector<float>> create_cone(float radius, float height, int slices, int stacks);

/*
* Função que cria um array de pontos para construir a esfera
*/
std::tuple<t_points, t_points, std::vector<float>> create_sphere(int radius, int slices, int stacks);

/*
* Função que cria um array de pontos para construir o cilindro
*/
std::tuple<t_points, t_points, std::vector<float>> create_cylinder(int radius, int height, int slices, int stacks);

std::tuple<t_points, t_points, std::vector<float>> create_torus(float radius, float size, int slices, int stack);

/*
Create a vector of list of points that can be drawn with line loop
*/
std::tuple<t_points, t_points, std::vector<float>> create_bezier(std::vector<std::vector<int>> patches, std::vector<Point> points, int level);

std::tuple<t_points, t_points, std::vector<float>>  create_sphere(int radius, int slices, int stacks, Point offset);

std::tuple<t_points, t_points, std::vector<float>> create_asteroids(double distMin, double distMax, int maxSize, int slices, int stacks, double alphaMax, double betaMax, int numAsteroids);
#endif // !SHAPES_DRAW
