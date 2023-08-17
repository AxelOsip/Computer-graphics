#include <iostream>
#include "window.h"

#include "tools.h"

#include "quaternion.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;


int main(int argc, char *argv[]){

	Quaternion h = Quaternion(vec4(2,1,3,1));	// init quat

	float t = M_PI/2;	// angle
	vec4 axis(0,0,1,0);	// z-axis

	Quaternion q = Quaternion(axis, t);			// rotation quat

	vec4 v_new = (q*h*~q).getVector();			// vec4(-1, 2, 3, 1)
	vec_debug(v_new);


	Window window;
	window.loop();
}