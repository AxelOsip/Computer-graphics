#include "canvas.h"


void Canvas::update(){

	ivec3 cross;
	
	line_0[0] = ivec3(50, 50, 1);
	line_0[1] = ivec3(450, 450, 1);
	drawLine(line_0[0], line_0[1], CL_RED);

	line_1[0] = ivec3(450, 50, 1);
	line_1[1] = ivec3(50, 450, 1);
	drawLine(line_1[0], line_1[1], CL_RED);

	line_2[0] = ivec3(100, 100, 1);
	line_2[1] = ivec3(100, 400, 1);
	drawLine(line_2[0], line_2[1], CL_RED);

	line_3[0] = ivec3(150, 150, 1);
	line_3[1] = ivec3(350, 150, 1);
	drawLine(line_3[0], line_3[1], CL_RED);

	if (crossPoint(line_0, line_1, cross))
		drawCircle(cross, 10, CL_YELLOW);

	if (crossPoint(line_0, line_2, cross))
		drawCircle(cross, 10, CL_YELLOW);

	if (crossPoint(line_0, line_3, cross))
		drawCircle(cross, 10, CL_YELLOW);

	if (crossPoint(line_1, line_2, cross))
		drawCircle(cross, 10, CL_YELLOW);
	
	if (crossPoint(line_1, line_3, cross))
		drawCircle(cross, 10, CL_YELLOW);

	if (crossPoint(line_2, line_3, cross))
		drawCircle(cross, 10, CL_YELLOW);

}


int Canvas::asserting(int x, int y){
	// Temporary asserting invalid parameters
	assert(surface != NULL);
	if (x >= surface->w || y >= surface->h || x < 0 || y < 0){
		printf("Point is out of bounce");
		return FAIL;
	}
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


int Canvas::crossPoint(Array<ivec3> &line_0, Array<ivec3> &line_1, ivec3 &cross){
	// Kramer's method for thee following equalities:
	//
	//	x_cross = x1 + (x2-x1)*t = x3 + (x4-x3)*k
	//	y_cross = y1 + (y2-y1)*t = y3 + (y4-y3)*k
	
	int dx_0 = line_0[1].x - line_0[0].x;	// x2 - x1
	int dx_1 = line_1[1].x - line_1[0].x;	// x4 - x3
	
	int dy_0 = line_0[1].y - line_0[0].y;	// y2 - y1
	int dy_1 = line_1[1].y - line_1[0].y;	// y4 - y3

	int dx_10 = line_1[0].x - line_0[0].x;	// x3 - x1
	int dy_10 = line_1[0].y - line_0[0].y;	// y3 - y1

	int det = dx_1 * dy_0 - dx_0 * dy_1;	// main determinant

	if (!det)
		return FAIL;	// lines are parallel
	
	int det_t = dx_1 * dy_10 - dx_10 * dy_1;
	int det_k = dx_0 * dy_10 - dx_10 * dy_0;
	float t = det_t / float(det);
	float k = det_k / float(det);

	if (t < 0 || t > 1 || k < 0|| k > 1)
		return FAIL;	// lines don t crossover
	cross.x = line_0[0].x + dx_0*t;
	cross.y = line_0[0].y + dy_0*t;
	return SUCCESS;
}

