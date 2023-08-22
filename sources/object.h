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

	Object(const char* path){
		ifstream file;
		file.open(path);
		if (!file.is_open()){
			cout << "cannot open file: " << path;
			abort();
		}
		readFile(file);
		file.close();
	};
	~Object(){};

	void readFile(ifstream &file);
	void setMatrix(int size, int dx, int dy, int dz);
	void scale(float scale);
	void shift(int dx, int dy, int dz);

	Array<vec4> points{0};
	Array<vec3> connections{0};
	Array<vec4> normals{0};
	Array<int> normal_id{0};

	vec4 center{0,0,0,0};		// center point
	mat4 matrix = MAT4_EYE;		// transform matrix
};