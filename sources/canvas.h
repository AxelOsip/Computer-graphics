#include <iostream>
#include <math.h>
using namespace std;

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

		for (int i = 0; i < 10; i++){
			float angle = 2*M_PI/10*i;
			int x = cos(angle)* (0.5 + 0.5*(i%2)) * 150;
			int y = sin(angle)* (0.5 + 0.5*(i%2)) * 150;
			poly[i] = ivec3(x+250,y+250,1);
		}
	}
	void update();											// Updating canvas


	private:

	Array<ivec3> poly{10}; 

	SDL_Surface* surface;
	int asserting(int x, int y);							// (!) temporary asserting of parameters
	
	void setPixel(ivec3 cord, uint32 color);  				// setting color into canvas pixel; vec2{x, y}
	void setPixel(int x, int y, uint32 color);				// setting color into canvas pixel; {x, y}

	uint32 getPixel(ivec3 cord);							// getting color from canvas pixel; vec2{x, y}
	uint32 getPixel(int x, int y);							// getting color from canvas pixel; {x, y}
	
	void drawLine(ivec3 pt_1, ivec3 pt_2, uint32 color);	// drawing line between two points; vec2(x, y)
	void drawCircle(ivec3 center, int radius, uint32 color);// drawing circle using center and radius;
	void drawPoly(Array<ivec3> &pts, uint32 color);			// drawing poly
	void fillPoly(Array<ivec3> &pts, uint32 color);			// filling area inside a poly

	int crossPoint(Array<ivec3> &line_0, Array<ivec3> &line_1, ivec3 &cross);		// finding point of crossing of two lines (Array, size=2)
	int crossPoint(ivec3 pt_1, ivec3 pt_2, ivec3 pt_3, ivec3 pt_4, ivec3 &cross);	// finding point of crossing of two lines (pt_1-pt_2, pt_3-pt_4)

};
