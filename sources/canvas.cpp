#include "canvas.h"


void Canvas::update(){

	// Array<int> array(5, true);
	
	// for (int i = 0; i < 5; i++){
	// 	array[i] = i;	
	// 	printf("%d, ", array[i]);
	// }
	// printf("\n");

	// if(!array.resize(7))
	// 	abort();

	// for (int i = 0; i < 7; i++){
	// 	array[i] = i;	
	// 	printf("%d, ", array[i]);
	// }
	// printf("\n");

	drawCircle(ivec3(250,250,0), 150, CL_RED);

	// printf("Press any button to exit.");
	// getchar();
	// exit(0);

	
	
}


int Canvas::asserting(int x, int y){
	// Temporary asserting invalid parameters
	assert(surface != NULL);
	if (x >= surface->w || y >= surface->h || x < 0 || y < 0)
		return FAIL;
	return SUCCESS;
	// assert(x < surface->w);
    // assert(y < surface->h);
    // assert(x >= 0);
    // assert(y >= 0);
}


void Canvas::setPixel(ivec3 cord, uint32 color){
	setPixel(cord.x, cord.y, color);
}

void Canvas::setPixel(int x, int y, uint32 color){
	if (!asserting(x, y))
		return;
	uint32 *pixels = (uint32*)surface->pixels;
	pixels[(y * surface->w) + x] = color;
}


uint32 Canvas::getPixel(ivec3 cord){
	return getPixel(cord.x, cord.y);
}

uint32 Canvas::getPixel(int x, int y){
	if (!asserting(x, y))
		return CL_BLACK;
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
		if (abs(cord_real - cord[!key]) > 0.5)
			cord[!key] += delta[!key];
		setPixel(cord, color);
	}
}


void Canvas::drawCircle(ivec3 center, int radius, uint32 color){
	// The Bresenham's circle algorithm
	ivec3 cord{	center.x, 
				center.y+radius, 1};
	
	for (int i = 0; i < radius*sin(M_PI/4); i++){
		// Calcilating one segmaent (1/8) of the circle
		cord.x = center.x + i;
		float y_real = sqrt(radius*radius - i*i) + center.y;
		if (cord.y - y_real > 0.5)
			cord.y--;

		// Calculating others segments of the circle
		for (int j = 0; j < 8; j++){
			ivec3 cord_mir = cord;
			cord_mir = cord_mir * MAT_shift(-center.x, -center.y);	// transport center to the (0, 0) cord 
			if (j & 1)
				cord_mir = cord_mir * MAT_mir_Ox;					// mirroring Ox
			if (j & 2)
				cord_mir = cord_mir * MAT_mir_Oy;					// mirroring Oy
			if (j & 4)
				cord_mir = cord_mir * MAT_mir_xy;					// mirroring xy
			cord_mir = cord_mir * MAT_shift(center.x, center.y);	// transport center back
			setPixel(cord_mir, color);
		}
	}
}
