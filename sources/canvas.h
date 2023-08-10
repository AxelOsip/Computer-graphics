#include <stdio.h>
#include <cassert>
#include <math.h>

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "tools.h"
#include "smartArray.h"


class Canvas{

	public:

	Canvas(){};
	~Canvas(){};
	void setSurface(SDL_Surface* surface){					// Setting surface
		this->surface = surface;
	}
	void update();											// Updating canvas


	private:

	Array<ivec3> line_0 = Array<ivec3>(2);
	Array<ivec3> line_1 = Array<ivec3>(2);
	Array<ivec3> line_2 = Array<ivec3>(2);
	Array<ivec3> line_3 = Array<ivec3>(2);

	SDL_Surface* surface;
	int asserting(int x, int y);							// (!) Temporary asserting invalid parameters


	void setPixel(ivec3 cord, uint32 color);				// Setting the color into canvas pixel; vec2{x, y} 
	void setPixel(int x, int y, uint32 color);				// Setting the color into canvas pixel; {x, y}

	uint32 getPixel(ivec3 cord);							// Getting the colot from canvas pixel; vec2{x, y}
	uint32 getPixel(int x, int y);							// Getting the colot from canvas pixel; {x, y}
	
	void drawLine(ivec3 pt_1, ivec3 pt_2, uint32 color);	// Drawing line between two points; vec2(x, y)
	void drawCircle(ivec3 center, int radius, uint32 color);// Drawing Circle using center and radius;

	int crossPoint(Array<ivec3> &line_0, Array<ivec3> &line_1, ivec3 &cross);			// finding point of crossing of two lines (size=2)

};
