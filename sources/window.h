#pragma once

#include <stdio.h>

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "tools.h"
#include "canvas.h"


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

	const int FPS = 60;													// Window FPS setting
	const char* header = "Attention! High-risk zone. Do not enter!.";   // Window header
	const vec2 resolution{500,500};                                     // Window resolution; vec2(width, height)
	Canvas canvas;											// Canvas for drawing on

	int init();															// Window initialization
	void close();														// Window closing
	void event(bool*);                          						// keyboard and mouse event processor                       

	public:

	void loop();														// Infinity loop

};

