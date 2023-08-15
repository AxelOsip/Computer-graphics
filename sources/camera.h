#pragma once
#include <iostream>
using namespace std;

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "tools.h"
#include "smartArray.h"
#include "canvas.h"


class Camera{
	public:

	Camera(){};
	~Camera(){};

	ivec3 projection(vec4 pt);						// project point to camera surface
	void rotate(float angle_Ox, float angle_Oy);	// rotate camera (angle in radians)
	
	private:

	vec4 position{0,0,0,0};

	// projection surface local direction
	vec4 right = RIGHT;			// local x
	vec4 up = UP;				// local y
	vec4 forward = FORWARD;		// local z

};