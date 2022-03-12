#include "writer.h"

// ---------------------------- Funções Auxiliares -------------------------------------
/*
* Função criada para escrever no documento xml um ponto 
*/
void write_point(XMLDocument* xml, tuple<float, float, float> point) {
	XMLNode* root = xml->FirstChild();

	XMLElement* ponto = xml->NewElement("point");
	ponto->SetAttribute("x", get<0>(point));
	ponto->SetAttribute("y", get<1>(point));
	ponto->SetAttribute("z", get<2>(point));
	root->InsertEndChild(ponto);
}

/*
* Função para escrever todo o ficheiro xml, relativo a uma figura gemométrica
*/
void write_xml(const char* filepath, GLenum type, t_points* all_points) {
	XMLDocument xml;
	int size = all_points->size;

	XMLNode* pRoot = xml.NewElement("Geometry");
	xml.InsertFirstChild(pRoot);

	XMLElement* model = xml.NewElement("model");
	model->SetAttribute("type", type);
	model->SetAttribute("size", size);

	pRoot->InsertEndChild(model);

	for (int i = 0; i < size; i++)
	{
		write_point(&xml, all_points->points[i]);
	}

	XMLError eres = xml.SaveFile(filepath);
}

// ------------------------------------------------------------------------------------

int main(int argc, const char** argv) {
	
	if (argc < 5 || argc > 6) {
		cout << "Args: ./generator _GEO-FORM_ _PARAMS_ _FILEPATH_";
	}

	t_points* points;

	if (strcmp(argv[1], "sphere") == 0) {
		if (argc < 6) {
			cout << "Insufficient Args.Example: ./generator sphere radius slices stacks sphere.3d";
		}

		int radius = std::atoi(argv[2]);
		int slices = std::atoi(argv[3]);
		int stacks = std::atoi(argv[4]);

		points = create_sphere(radius, slices, stacks);

		write_xml(argv[5], GL_TRIANGLES, points);
	
	}else if (strcmp(argv[1], "box") == 0) {
		if (argc < 5) {
			cout << "Insufficient Args.Example: ./generator box units divisions box.3d";
		}

		float units = std::stof(argv[2]);
		int divisions = std::atoi(argv[3]);

		points = create_box(units, divisions);

		write_xml(argv[4], GL_TRIANGLES, points);
	
	}
	else if (strcmp(argv[1], "cone") == 0) {
		if (argc < 7) {
			cout << "Insufficient Args.Example: ./generator cone radius height slices stacks cone.3d";
		}

		int radius = std::atoi(argv[2]);
		int height = std::atoi(argv[3]);
		int slices = std::atoi(argv[4]);
		int stacks = std::atoi(argv[5]);

		points = create_cone(radius, height, slices, stacks);

		write_xml(argv[6], GL_TRIANGLES, points);
	
	}
	else if (strcmp(argv[1], "plane") == 0) {
		if (argc < 5) {
			cout << "Insufficient Args.Example: ./generator cone radius height slices stacks cone.3d";
		}

		float length = std::stof(argv[2]);
		int divisions = std::atoi(argv[3]);

		points = create_plane(length, divisions);

		write_xml(argv[4], GL_TRIANGLES, points);
	
	}
	else {
		cout << "Geometric Figures: sphere | cone | box | plane";
	}

	return 1;
}