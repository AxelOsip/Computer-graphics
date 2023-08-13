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
#include "camera.h"
#include "object.h"


class Scene{

	public:

	Scene(){
		cube.setMatrix(100, 250,250,1);
		// cube.scale(1.5);
		// cube.shift(150,0,0);
	}
	~Scene(){}
	void setCanvas(Canvas &canvas){
		this->canvas = canvas;
	}

	void update();
	ivec3 projection(vec4 pt);

	private:

	void drawObj(Object &obj);

	Object cube{"objects/cube.obj"};

	Canvas canvas;
	Camera camera;

};