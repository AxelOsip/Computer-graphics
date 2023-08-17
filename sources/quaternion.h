#pragma once

#include <iostream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;


class Quaternion{

	// a + b*i + c*j + d*k
	// 0 + x*i + y*j + z*k

	public:

	Quaternion(vec4 v);
	Quaternion(float a, float b, float c, float d);
	Quaternion(vec4 axis, float angle);
	~Quaternion(){}

	
	Quaternion operator * (Quaternion q);
	Quaternion operator ~ ();
	
	vec4 getVector();
	
	
	void debug();

	float a, b, c, d;



};