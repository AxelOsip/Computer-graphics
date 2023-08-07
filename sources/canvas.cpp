

#include "canvas.h"


void Canvas::update(){

	// Demonstration of the circle
	for (float t = 0; t < 2*M_PI; t = t + 0.01){
		int x = 100*cos(t) + 250;
		int y = 100*sin(t) + 250;
		setPixel(x, y, CL_RED);
	}
	
}


void Canvas::asserting(int x, int y){
	// Temporary asserting invalid parameters
	assert(surface != NULL);
	assert(x < surface->w);
    assert(y < surface->h);
    assert(x >= 0);
    assert(y >= 0);
}


void Canvas::setPixel(ivec2 cord, uint32 color){
	setPixel(cord.x, cord.y, color);
}

void Canvas::setPixel(int x, int y, uint32 color){
	asserting(x, y);
	uint32 *pixels = (uint32*)surface->pixels;
	pixels[(y * surface->w) + x] = 0x00ff0000;
}


uint32 Canvas::getPixel(ivec2 cord){
	return getPixel(cord.x, cord.y);
}

uint32 Canvas::getPixel(int x, int y){
	asserting(x, y);
	uint32 *pixels = (uint32*)surface->pixels;
    return pixels[(y * surface->w) + x];
}