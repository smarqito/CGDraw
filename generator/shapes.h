#ifndef SHAPES_DRAW
#include <tuple>
#include <math.h>
#include <vector>
#include "../cartesian/cartesian.h"
#include "../cartesian/Curve.h"

using namespace std;


/*
* Fun��o que cria um array de pontos para construir o plano
*
*/
t_points create_plane(double length, int divisions);

/*
* Fun��o que cria um array de pontos para construir uma caixa
*/
t_points create_box(double units, int divisions);

/*
* Fun��o que cria um array de pontos para construir o cone
*/
t_points create_cone(double radius, double height, int slices, int stacks);

/*
* Fun��o que cria um array de pontos para construir a esfera
*/
t_points create_sphere(int radius, int slices, int stacks);

/*
* Fun��o que cria um array de pontos para construir o cilindro
*/
t_points create_cylinder(int radius, int height, int slices, int stacks);

t_points create_torus(double radius, double size, int slices, int stack);

/*
Create a vector of list of points that can be drawn with line loop
*/
vector<t_points> create_bezier(vector<vector<int>> patches, vector<point> points, int level);
#endif // !SHAPES_DRAW
