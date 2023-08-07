#pragma once

#include <stdio.h>

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "tools.h"


class Window{

	public:
	
	Window(){
		this->init();
	}

	~Window(){
		close();
	}
	

	private:

	SDL_Window *ptrWindow = NULL;
	SDL_Renderer *ptrRenderer = NULL;
	SDL_Texture *ptrTexture = NULL;
	SDL_Surface *ptrSurface = NULL;

	const int FPS = 60;

	const char* header = "Attention! High-risk zone. Do not enter!.";   // Window header
	const vec2 resolution{500,500};                                     // Window resolution; vec2(width, height)

	int init();
	void close();
	void event(bool*);                                                 

	public:

	void loop();

};

