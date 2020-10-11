#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Shader
{
private:
	string m_shaderStr;
public:
	Shader(string fileName) {
		setShader(fileName);
	}

	void setShader(string fileName) {
		m_shaderStr = "";
		fileName = "C:\\Users\\Chandra\\source\\repos\\opengl_intro\\src\\" + fileName;
		ifstream file;
		string line;

		file.open(fileName);
		if (file.is_open()) {
			while (getline(file, line)) {
				m_shaderStr += line + "\n";
			}
			file.close();
		}
		else cout << "Can't open file \'" << fileName << "\'\n";
	}

	const char* getShader() {
	//void getShader() {
		/*nt len = m_shaderStr.length();
		const char* result = new const char[len];

		for (int i = 0; i < len; i++) {
			result[i] = m_shaderStr[i];
		}*/
		return m_shaderStr.c_str();
	}

	void printShader() { cout << m_shaderStr; }
};
