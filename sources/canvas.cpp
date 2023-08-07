

#include "canvas.h"


void Canvas::update(){

	// Demonstration of the circle
	vec3 center{250, 250, 1};
	int count = 32;
	for (float t = 0; t < count; t++){
		vec3 pt_i{150*cos(2*M_PI/count*t),
				  150*sin(2*M_PI/count*t), 1};
		drawLine(center, center + pt_i, CL_RED);
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


void Canvas::setPixel(ivec3 cord, uint32 color){
	setPixel(cord.x, cord.y, color);
}

void Canvas::setPixel(int x, int y, uint32 color){
	asserting(x, y);
	uint32 *pixels = (uint32*)surface->pixels;
	pixels[(y * surface->w) + x] = 0x00ff0000;
}


uint32 Canvas::getPixel(ivec3 cord){
	return getPixel(cord.x, cord.y);
}

uint32 Canvas::getPixel(int x, int y){
	asserting(x, y);
	uint32 *pixels = (uint32*)surface->pixels;
    return pixels[(y * surface->w) + x];
}


void Canvas::drawLine(ivec3 pt_1, ivec3 pt_2, uint32 color){
	// The Bresenham's line algorithm
	// for every direction of line

	float k;
	if (pt_2.x-pt_1.x == 0)
		k = 1000;
	else 
		k = float(pt_2.y-pt_1.y) / (pt_2.x-pt_1.x);
	float b = -pt_1.x * k + pt_1.y;
	bool key = abs(k) > 1? 1: 0;

	ivec3 dir = pt_2 - pt_1;
	ivec2 delta{dir.x > 0 ? 1: -1,
				dir.y > 0 ? 1: -1};

	ivec3 cord = pt_1;
	float cord_real = pt_1[!key];
	for (int i = pt_1[key]; i != pt_2[key]; i += delta[key]){
		cord[key] = i;
		if (key)
			cord_real = (cord[1]-b)/k;
		else
			cord_real = k*cord[0] + b;
		// printf("%f\n", cord_real);
		if (abs(cord_real - cord[!key]) > 0.5)
			cord[!key] += delta[!key];
		setPixel(cord, color);
	}
}
