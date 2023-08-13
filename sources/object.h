#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "tools.h"
#include "smartArray.h"


class Object{

	public:
	Object(){
		const char* path = "objects/cube.obj";
		file.open(path);
		if (!file.is_open()){
			cout << "cannot open file: " << path;
			abort();
		}
		readFile(file);
		file.close();
	}
	~Object(){}

	void readFile(ifstream &file);

	ifstream file;

	Array<vec4> points{0};
	Array<vec3> connections{0};
	Array<vec4> normals{0};

	mat3 matrix = MAT_EYE * 150;		// transformation matrix
};