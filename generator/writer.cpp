#include <tinyxml2.h>
#include <iostream>
#include <string>
#include <tuple>
#include <GL/glut.h>

using namespace std;
using namespace tinyxml2;

struct t_points {
	tuple<double, double, double>* points;
	int size;
};


void write_point(XMLDocument* xml, tuple<double, double, double> point) {
	XMLNode* root = xml->FirstChild();

	XMLElement* ponto = xml->NewElement("point");
	ponto->SetAttribute("x", get<0>(point));
	ponto->SetAttribute("y", get<1>(point));
	ponto->SetAttribute("z", get<2>(point));
	root->InsertEndChild(ponto);
}

void write_xml(char* filename, GLenum type, t_points* points) {
	XMLDocument xml;

	XMLElement* model = xml.NewElement("model");
	model->SetAttribute("type", type);
	model->SetAttribute("size", points->size);

	for (int i = 0; i < points->size; i++)
	{
		write_point(&xml, points->points[i]);
	}
}

int main(int argc, char** argv) {
	XMLDocument* xml = new XMLDocument();
	//xml.LoadFile("teste.xml");

	XMLElement* elem = xml->NewElement("model");
	elem->SetAttribute("type", 1);
	xml->InsertFirstChild(elem);
	for (int i = 0; i < 100; i++)
	{
		write_point(xml, tuple<double, double, double>(i,i,i));
	}

	XMLError eres = xml->SaveFile("/home/smarqito/teste.xml");
	std::cout << eres;

}