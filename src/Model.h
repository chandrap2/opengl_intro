#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Model {
private:
	std::vector<float> vertices;
	std::vector<short> vertInd;
public:
	Model(string modelFile);
	void readModel(string modelFile);
	void setVerts(float* verts, short* ind);

	int getVertSize();
	int getIndSize();
};