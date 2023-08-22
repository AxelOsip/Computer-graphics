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
		cube.setMatrix(2, 0,0,5);
		tetra.setMatrix(2, 2,1,2);
	}
	~Scene(){}
	void setCanvas(Canvas &canvas){
		this->canvas = canvas;
	}
	void setCenter(ivec2 center){
		camera.setCenter(center);
	}
	void setResolution(ivec2 resolution){
		camera.setResolution(resolution);
	}

	void update();
	void control(const uint8 *keys);
	void control(int x, int y);


	private:

	void drawObj(Object &obj);
	void fillObj(Object &obj);
	ivec3 projection(vec4 pt);

	Object cube{"objects/cube.obj"};
	Object tetra{"objects/tetrahedra.obj"};

	Canvas canvas;
	Camera camera{};

	float step = 0.05;				// move step per frame
	float sensitivity = 0.002;		// rotate step per frame

};