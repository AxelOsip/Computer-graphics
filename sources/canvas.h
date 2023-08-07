#include <stdio.h>
#include <cassert>
#include <math.h>

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "tools.h"


class Canvas{

	public:

	Canvas(){};
	~Canvas(){};
	void setSurface(SDL_Surface* surface){	// Setting surface
		this->surface = surface;
	}
	void update();							// Updating canvas


	private:

	SDL_Surface* surface;
	void asserting(int x, int y);			// (!) Temporary asserting invalid parameters

	void setPixel(ivec2, uint32);			// Setting the color into canvas pixel; format: vec2{x, y} 
	void setPixel(int, int, uint32);		// Setting the color into canvas pixel; format: x, y

	uint32 getPixel(ivec2 cord);			// Getting the colot from canvas pixel; format: vec2{x, y}
	uint32 getPixel(int x, int y);			// Getting the colot from canvas pixel; format: x, y

};
