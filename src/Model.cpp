#include "Model.h"
using namespace std;

Model::Model(string modelFile) {
	readModel(modelFile);
}

void Model::readModel(string modelFile) {
	modelFile = "C:\\Users\\Chandra\\source\\repos\\opengl_intro\\src\\" + modelFile;
	ifstream file; string line;
		
	file.open(modelFile);
	getline(file, line);
	int numVerts = stoi(line);
	this->vertices.reserve(numVerts * 5);
	//cout << numVerts << endl;
	
	float x, y, r, g, b;
	istringstream ss;
	for (int i = 0; i < numVerts; i++) {
		ss.clear();
		getline(file, line);
		ss.str(line);
		ss >> x >> y;
		this->vertices.push_back(x);
		this->vertices.push_back(y);

		ss.clear();
		getline(file, line);
		ss.str(line);
		ss >> r >> g >> b;
		this->vertices.push_back(r);
		this->vertices.push_back(g);
		this->vertices.push_back(b);

		std::cout << x << ", " << y << std::endl;
		std::cout << r << ", " << g << ", " << b << std::endl << std::endl;
	}

	std::cout << std::endl;

	int p1, p2, p3;
	while (getline(file, line)) {
		ss.clear();
		ss.str(line);
		ss >> p1 >> p2 >> p3;

		this->vertInd.push_back(p1);
		this->vertInd.push_back(p2);
		this->vertInd.push_back(p3);
		std::cout << p1 << ", " << p2 << ", " << p3 << std::endl;
	}

	file.close();
}

void Model::setVerts(float* verts, short* ind) {
	for (int i = 0; i < this->vertices.size(); i++) {
		verts[i] = this->vertices[i];
		//std::cout << verts[i] << std::endl;;
	}
	//std::cout << std::endl;
	
	for (int i = 0; i < this->vertInd.size(); i++) {
		ind[i] = this->vertInd[i];
		//std::cout << ind[i] << std::endl;
	}
	std::cout << std::endl;
}

int Model::getVertSize() { return this->vertices.size(); }
int Model::getIndSize() { return this->vertInd.size(); }
