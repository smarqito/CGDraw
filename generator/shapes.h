#ifndef SHAPES_DRAW

/*
* Estrutura de dados dos pontos para construir uma figura geom�trica
* Os pontos s�o tuplos -> coordenadas cartesianas x y z
* Os membros s�o:
*	points -> Array de pontos
*	size   -> N�mero de pontos
*	pos    -> Posi��o atual no array
*/
struct t_points {
	tuple<float, float, float>* points;
	int size;
	int pos;
};

/*
* Fun��o que cria um array de pontos para construir o plano
*
*/
t_points* create_plane(float length, int divisions);

/*
* Fun��o que cria um array de pontos para construir uma caixa
*/
t_points* create_box(float units, int divisions);

/*
* Fun��o que cria um array de pontos para construir o cone
*/
t_points* create_cone(float radius, float height, int slices, int stacks);

/*
* Fun��o que cria um array de pontos para construir a esfera
*/
t_points* create_sphere(int radius, int slices, int stacks);

#endif // !SHAPES_DRAW
