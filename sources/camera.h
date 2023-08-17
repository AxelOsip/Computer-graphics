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
#include "quaternion.h"


class Camera{
	public:

	Camera(){};
	~Camera(){};

	void setCenter(ivec2 center){
		this->center = center;
	}

	ivec3 projection(vec4 pt);						// project point to camera surface
	void rotate_hor(float angle);					// rotate arond global Oy
	void rotate_vert(float angle);					// rotate arond local Ox
	void shift(float dx, float dy, float dz);		// shift camera
	
	private:

	vec4 position{0,0,0,1};
	ivec2 center;						// image centering
	// projection surface local direction
	vec4 right = RIGHT;					// local Ox
	vec4 up = UP;						// local Oy
	vec4 forward = FORWARD;				// local Oz

	vec4 focus = vec4(0,0,-250,1);					// focus point for perspective projection

};