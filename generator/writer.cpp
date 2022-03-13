#include "writer.h"
#include "shapes.h"

// ---------------------------- Funções Auxiliares -------------------------------------
/*
* Função criada para escrever no documento xml um ponto
*/
void write_point(XMLDocument* xml, point point) {
	XMLNode* root = xml->FirstChild();

	XMLElement* ponto = xml->NewElement("point");
	ponto->SetAttribute("x", point.x);
	ponto->SetAttribute("y", point.y);
	ponto->SetAttribute("z", point.z);
	root->InsertEndChild(ponto);
}

/*
* Função para escrever todo o ficheiro xml, relativo a uma figura gemométrica
*/
void write_xml(const char* filepath, GLenum type, t_points all_points) {
	XMLDocument xml;
	int size = all_points.size();

	XMLElement* pRoot = xml.NewElement("model");
	xml.InsertFirstChild(pRoot);

	pRoot->SetAttribute("type", type);
	pRoot->SetAttribute("size", size);

	for (int i = 0; i < size; i++)
	{
		write_point(&xml, all_points.get_point(i));
	}

	xml.SaveFile(filepath);
}

// ------------------------------------------------------------------------------------

int main(int argc, const char** argv) {

	if (argc < 5 || argc > 7) {
		cout << "Args: ./generator _GEO-FORM_ _PARAMS_ _FILEPATH_";
		return 1;
	}

	t_points points(0);

	if (strcmp(argv[1], "sphere") == 0) {
		if (argc < 6) {
			cout << "Insufficient Args.Example: ./generator sphere radius slices stacks sphere.3d";
		}

		int radius = std::atoi(argv[2]);
		int slices = std::atoi(argv[3]);
		int stacks = std::atoi(argv[4]);

		points = create_sphere(radius, slices, stacks);

		write_xml(argv[5], GL_TRIANGLES, points);

	}
	else if (strcmp(argv[1], "box") == 0) {
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
			cout << "Insufficient Args.Example: ./generator plane length slices plane.3d";
		}

		float length = std::stof(argv[2]);
		int divisions = std::atoi(argv[3]);

		points = create_plane(length, divisions);

		write_xml(argv[4], GL_TRIANGLES, points);

	}
	else {
		cout << "Geometric Figures: sphere | cone | box | plane";
	}

	return 0;
}