#ifndef SHAPES_DRAW

/*
* Estrutura de dados dos pontos para construir uma figura geométrica
* Os pontos são tuplos -> coordenadas cartesianas x y z
* Os membros são:
*	points -> Array de pontos
*	size   -> Número de pontos
*	pos    -> Posição atual no array
*/
struct t_points {
	tuple<float, float, float>* points;
	int size;
	int pos;
};

/*
* Função que cria um array de pontos para construir o plano
*
*/
t_points* create_plane(float length, int divisions);

/*
* Função que cria um array de pontos para construir uma caixa
*/
t_points* create_box(float units, int divisions);

/*
* Função que cria um array de pontos para construir o cone
*/
t_points* create_cone(float radius, float height, int slices, int stacks);

/*
* Função que cria um array de pontos para construir a esfera
*/
t_points* create_sphere(int radius, int slices, int stacks);

#endif // !SHAPES_DRAW
