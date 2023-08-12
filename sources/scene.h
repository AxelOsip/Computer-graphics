#pragma once
#include <iostream>
using namespace std;

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "tools.h"
#include "smartArray.h"
#include "camera.h"


class Scene{

	public:

	Scene(){}
	~Scene(){}
	void setCanvas(Canvas &canvas){
		this->canvas = canvas;
	}

	void update();

	
	private:

	Canvas canvas;
	Camera camera{};

};