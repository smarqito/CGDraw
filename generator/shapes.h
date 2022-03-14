#ifndef SHAPES_DRAW
#include <tuple>
#include <math.h>
#include "../cartesian/cartesian.h"

using namespace std;


/*
* Função que cria um array de pontos para construir o plano
*
*/
t_points create_plane(double length, int divisions);

/*
* Função que cria um array de pontos para construir uma caixa
*/
t_points create_box(double units, int divisions);

/*
* Função que cria um array de pontos para construir o cone
*/
t_points create_cone(double radius, double height, int slices, int stacks);

/*
* Função que cria um array de pontos para construir a esfera
*/
t_points create_sphere(int radius, int slices, int stacks);

/*
* Função que cria um array de pontos para construir o cilindro
*/
t_points create_cylinder(int radius, int height, int slices, int stacks);

t_points create_torus(double radius, double size, int slices, int stack);
#endif // !SHAPES_DRAW
