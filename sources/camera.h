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

	
	private:

	vec4 position{0,0,0,0};
	vec4 direction = FORWARD;

};