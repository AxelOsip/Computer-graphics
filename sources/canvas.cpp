#include "canvas.h"


void Canvas::update(){

	fillPoly(poly, CL_RED);
	drawPoly(poly, CL_YELLOW);
	
}


int Canvas::asserting(int x, int y){
	// Temporary asserting invalid parameters
	assert(surface != NULL);
	if (x >= surface->w || y >= surface->h || x < 0 || y < 0){
		cout << "Point is out of bounce\n";
		return FAIL;
	}
	return SUCCESS;
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

void Canvas::drawPoly(Array<ivec3> &poly, uint32 color){
	for (int i = 0; i < poly.size; i++){
		drawLine(poly[i], poly[(i+1)%poly.size], color);
	}
}

void Canvas::fillPoly(Array<ivec3> &poly, uint32 color){
	int y_max = poly[0].y;
	int y_min = poly[0].y;
	for (int i = 1; i < poly.size; i++){		// getting highest and lower y level
		y_max = poly[i].y > y_max? poly[i].y: y_max;
		y_min = poly[i].y < y_min? poly[i].y: y_min;
	}

	static Array<ivec3> scan(2);				// scanning horizontal line
	static Array<ivec3> crosses(2, true);		// array of cross points of scan and poly

	for (int y = y_min; y < y_max; y++){
		scan[0] = ivec3(0, y, 1);				// left point
		scan[1] = ivec3(surface->w, y, 1);		// right point

		size_t cross_count = 0;
		
		// finding crosses
		for (int i = 0; i < poly.size; i++){
			int j = (i+1) % poly.size;
			ivec3 cross;
			if (crossPoint(scan[0], scan[1], poly[i], poly[j], cross)){
				cross_count++;
				crosses.resize((cross_count+1)/2*2);
				crosses[cross_count-1] = cross;
			}
		}
		
		// drawing horizontal line
		for (int i = 0; i < cross_count/2*2-1; i+=2){
			if (cross_count%2 == 1 && crosses[i].x == crosses[i+1].x)
				i++;
			drawLine(crosses[i], crosses[i+1], color);
		}
	}
}


int Canvas::crossPoint(Array<ivec3> &line_0, Array<ivec3> &line_1, ivec3 &cross){
	return crossPoint(line_0[0], line_0[1], line_1[0], line_1[1], cross);
}

int Canvas::crossPoint(ivec3 pt_1, ivec3 pt_2, ivec3 pt_3, ivec3 pt_4, ivec3 &cross){
	// 	Kramer's method for thee following equalities:
	//
	//	x_cross = x1 + (x2-x1)*t = x3 + (x4-x3)*k
	//	y_cross = y1 + (y2-y1)*t = y3 + (y4-y3)*k
	
	int dx_0 = pt_2.x - pt_1.x;	// x2 - x1
	int dx_1 = pt_4.x - pt_3.x;	// x4 - x3
	
	int dy_0 = pt_2.y - pt_1.y;	// y2 - y1
	int dy_1 = pt_4.y - pt_3.y;	// y4 - y3

	int dx_10 = pt_3.x - pt_1.x;	// x3 - x1
	int dy_10 = pt_3.y - pt_1.y;	// y3 - y1

	int det = dx_1 * dy_0 - dx_0 * dy_1;	// main determinant

	if (!det)
		return FAIL;	// lines are parallel
	
	int det_t = dx_1 * dy_10 - dx_10 * dy_1;
	int det_k = dx_0 * dy_10 - dx_10 * dy_0;
	float t = det_t / float(det);
	float k = det_k / float(det);

	if (t < 0 || t > 1 || k < 0|| k > 1)
		return FAIL;	// lines don t crossover
	cross.x = pt_1.x + dx_0*t;
	cross.y = pt_1.y + dy_0*t;
	return SUCCESS;
}
