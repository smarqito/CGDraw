#include "writer.h"
#include "shapes.h"
#include <bits/stdc++.h>

// ---------------------------- Fun��es Auxiliares -------------------------------------
/*
* Fun��o criada para escrever no documento xml um ponto
*/
void write_point(XMLDocument* xml, point point) {
	XMLNode* root = xml->FirstChild();

	XMLElement* ponto = xml->NewElement("point");
	ponto->SetAttribute("x", point.x);
	ponto->SetAttribute("y", point.y);
	ponto->SetAttribute("z", point.z);
	root->InsertEndChild(ponto);
}

void write_point(XMLDocument * xml, XMLElement * elem, point point) {
	XMLElement* ponto = xml->NewElement("point");
	ponto->SetAttribute("x", point.x);
	ponto->SetAttribute("y", point.y);
	ponto->SetAttribute("z", point.z);
	elem->InsertEndChild(ponto);
}


/*
* Fun��o para escrever todo o ficheiro xml, relativo a uma figura gemom�trica
*/
void write_xml(const char* filepath, GLenum type, t_points all_points) {
	XMLDocument xml;
	int size = all_points.total();

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

void write_xml_patch(const char* filepath, GLenum type, vector<t_points> all_points) {
	XMLDocument xml;
	int size = all_points.size();

	XMLElement* pRoot = xml.NewElement("model");
	xml.InsertFirstChild(pRoot);

	pRoot->SetAttribute("type", type);
	pRoot->SetAttribute("size", size);
	pRoot->SetAttribute("vbo", "False");
	pRoot->SetAttribute("patches", size);

	for (int i = 0; i < size; i++)
	{
		XMLElement* patches = xml.NewElement("patches");
		pRoot->InsertEndChild(patches);
		for (int j = 0; j < all_points[i].total(); j++) {
			write_point(&xml, patches, all_points[i].get_point(j));
		}
	}

	xml.SaveFile(filepath);
}

/*string vector_to_string(vector<int> v) {
	stringstream result;
	copy(v.begin(), v.end(), ostream_iterator<int>(result, ","));
	string s = result.str();
	s = s.substr(0, s.length() - 1);
	return s;
}*/

/*
* Fun��o criada para escrever no documento xml indices
*/
/*void write_xml_indexes(const char* filepath, GLenum type, vector<vector<int>> indexes, vector<point> all_points, double level) {
	XMLDocument xml;
	int size = all_points.size();

	XMLElement* pRoot = xml.NewElement("model");
	xml.InsertFirstChild(pRoot);

	pRoot->SetAttribute("type", type);
	pRoot->SetAttribute("size", size);
	pRoot->SetAttribute("indexes", "True");
	if (type == 2) {
		pRoot->SetAttribute("bezier", level);
	}
	else {
		pRoot->SetAttribute("bezier", 0.0);
	}

	//write indexes
	XMLNode* indexs = xml.NewElement("indexes");
	//XMLElement* indexs = xml.NewElement("indexes");
	pRoot->InsertEndChild(indexs);
	for (int i = 0; i < indexes.size(); i++)
	{
		XMLElement* index = xml.NewElement("index");
		index->SetText(vector_to_string(indexes[i]).data());
		indexs->InsertEndChild(index);
	}
	XMLElement* points = xml.NewElement("points");
	pRoot->InsertEndChild(points);
	for (int j = 0; j < size; j++) {
		write_point_2(&xml, points, all_points[j]);
	}

	xml.SaveFile(filepath);
}*/

// ------------------------------------------------------------------------------------

int main(int argc, const char** argv) {

	if (argc == 1) {
		cout << "Args: ./generator _GEO-FORM_ _PARAMS_ _FILEPATH_";
		return 1;
	}

	t_points points(0);

	if (strcmp(argv[1], "sphere") == 0) {
		if (argc < 6) {
			cout << "Insufficient Args.Example: ./generator sphere radius slices stacks sphere.3d\n";
			return 1;
		}

		int radius = std::atoi(argv[2]);
		int slices = std::atoi(argv[3]);
		int stacks = std::atoi(argv[4]);

		points = create_sphere(radius, slices, stacks);

		write_xml(argv[5], GL_TRIANGLES, points);

	}
	else if (strcmp(argv[1], "box") == 0) {
		if (argc < 5) {
			cout << "Insufficient Args.Example: ./generator box units divisions box.3d\n";
			return 1;
		}

		float units = std::stof(argv[2]);
		int divisions = std::atoi(argv[3]);

		points = create_box(units, divisions);

		write_xml(argv[4], GL_TRIANGLES, points);

	}
	else if (strcmp(argv[1], "cone") == 0) {
		if (argc < 7) {
			cout << "Insufficient Args.Example: ./generator cone radius height slices stacks cone.3d\n";
			return 1;
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
			cout << "Insufficient Args.Example: ./generator plane length slices plane.3d\n";
			return 1;
		}

		float length = std::stof(argv[2]);
		int divisions = std::atoi(argv[3]);

		points = create_plane(length, divisions);

		write_xml(argv[4], GL_TRIANGLES, points);

	}
	else if (strcmp(argv[1], "cylinder") == 0) {
		if (argc < 7) {
			cout << "Insufficient Args.Example: ./generator cylinder radius height slices stacks cylinder.3d";
			return 1;
		}

		int radius = std::atoi(argv[2]);
		int height = std::atoi(argv[3]);
		int slices = std::atoi(argv[4]);
		int stacks = std::atoi(argv[5]);

		points = create_cylinder(radius, height, slices, stacks);

		write_xml(argv[6], GL_TRIANGLES, points);
	}
	else if (strcmp(argv[1], "torus") == 0) {
		if (argc < 7) {
			cout << "Insufficient Args.Example: ./generator cylinder radius size slices stacks cylinder.3d";
			return 1;
		}

		int radius = std::stof(argv[2]);
		int height = std::stof(argv[3]);
		int slices = std::atoi(argv[4]);
		int stacks = std::atoi(argv[5]);

		points = create_torus(radius, height, slices, stacks);

		write_xml(argv[6], GL_TRIANGLES, points);
	}
	else if (strcmp(argv[1], "bezier") == 0) {
		if (argc < 5) {
			cout << "Insufficient Args.Example: ./generator bezier namefile tessellationLevel bezier.3d";
			return 1;
		}
		fstream file;
		file.open(argv[2], ios::in);
		string tp;
		getline(file, tp);
		int patchs = stoi(tp);
		vector<vector<int>> v;
		for (int i = 0; i < patchs; i++) {
			getline(file, tp);
			vector<int> v2;
			regex regexp(R"(\d+)");
			smatch m;
			while (regex_search(tp, m, regexp)) {
				v2.push_back(stoi(m[0]));
				tp = m.suffix().str();
			}
			v.push_back(v2);
		}
		getline(file, tp);
		int npoints = stoi(tp);
		vector<point> _points;
		for (int i = 0; i < npoints; i++) {
			getline(file, tp);
			regex regexp(R"(([+-]?\d+(?:\.\d+)?), ([+-]?\d+(?:\.\d+)?), ([+-]?\d+(?:\.\d+)?))");
			smatch m;
			regex_search(tp, m, regexp);
			point p;
			p.x = stod(m[1]); p.y = stod(m[2]); p.z = stod(m[3]);
			_points.push_back(p);
		}
		file.close();
		vector<t_points> res = create_bezier(v, _points, stod(argv[3]));
		write_xml_patch(argv[4], GL_LINE_LOOP, res);

	}
	else {
		cout << "Geometric Figures: sphere | cone | box | plane | bezier";
	}

	return 0;
}