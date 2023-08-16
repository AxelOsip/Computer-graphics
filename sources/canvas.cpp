#include "canvas.h"


void Canvas::update(){
	clear();

	// ivec3 pt_1(500-100, -50, 1);
	// ivec3 pt_2(500+50, 100, 1);
	// ivec3 pt_1(450, -100, 1);
	// ivec3 pt_2(550, 50, 1);
	// drawLine(pt_1, pt_2, CL_RED);
}


int Canvas::validation(int x, int y){
	if (x >= surface.w || y >= surface.h || x < 0 || y < 0){
		cout << "Point is out of bounce\n";
		cout << x << " " << y << " " << endl;
		return FAIL;
	}
	return SUCCESS;
}


void Canvas::clear(){
	for (int x = 0; x < surface.w; x++)
		for (int y = 0; y < surface.h; y++)
			setPixel(x, y, CL_BLACK);
}


void Canvas::setPixel(ivec3 cord, uint32 color){
	setPixel(cord.x, cord.y, color);
}

void Canvas::setPixel(int x, int y, uint32 color){
	// if (!validation(x, y))
	// 	return;
	uint32 *pixels = (uint32*)surface.pixels;
	pixels[(y * surface.w) + x] = color;
}


uint32 Canvas::getPixel(ivec3 cord){
	return getPixel(cord.x, cord.y);
}

uint32 Canvas::getPixel(int x, int y){
	if (!validation(x, y))
		return CL_BLACK;
	uint32 *pixels = (uint32*)surface.pixels;
    return pixels[(y * surface.w) + x];
}


void Canvas::drawLine(ivec3 pt_1, ivec3 pt_2, uint32 color){
	// The Bresenham's line algorithm
	// for every line direction

	if (!cutLine(pt_1, pt_2))
		return;
	
	setPixel(pt_1, color);
	if (pt_1 == pt_2)
		return;
	
	ivec3 dir = pt_2 - pt_1;		// direction vector
	imat3 mirror = MAT3_EYE;		// mirror matrix 

	if (dir.y < 0)
		mirror = mirror * MAT3_mir_Ox;
	if (dir.x < 0)
		mirror = mirror * MAT3_mir_Oy;
	if (abs(dir.y) > abs(dir.x))
		mirror = mirror * MAT3_mir_xy;
	dir = dir * mirror;				// mirroring

	float k = dir.y / float(dir.x);	// division by zero will never happen
	float b = -pt_1.x * k + pt_1.y;

	float y_real = 0;
	int y = 0;
	for (int x = 1; x <= dir.x; x++){
		y_real += k;				// step in real
		if (y_real - y > 0.5)		// check difference between real and approximated
			y++;					// step in approximated
		ivec3 cord = pt_1 + ivec3(x,y,0) * MAT3_T(mirror);	// calc result point with mirroring back
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
			cord_mir = cord_mir * MAT3_shift(-center.x, -center.y);	// transport center to the (0, 0) cord 
			if (j & 1)
				cord_mir = cord_mir * MAT3_mir_Ox;					// mirroring Ox
			if (j & 2)
				cord_mir = cord_mir * MAT3_mir_Oy;					// mirroring Oy
			if (j & 4)
				cord_mir = cord_mir * MAT3_mir_xy;					// mirroring xy
			cord_mir = cord_mir * MAT3_shift(center.x, center.y);	// transport center back
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
	int x_max = poly[0].x;
	int x_min = poly[0].x;
	for (int i = 1; i < poly.size; i++){		// getting highest and lower y level
		y_max = poly[i].y > y_max? poly[i].y: y_max;
		y_min = poly[i].y < y_min? poly[i].y: y_min;
		x_max = poly[i].x > x_max? poly[i].x: x_max;
		x_min = poly[i].x < x_min? poly[i].x: x_min;
	}

	static Array<ivec3> scan(2);				// scanning horizontal line
	static Array<ivec3> crosses(2, true);		// array of cross points of scan and poly

	for (int y = y_min; y < y_max; y++){
		scan[0] = ivec3(x_min, y, 1);				// left point
		scan[1] = ivec3(x_max, y, 1);		// right point

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
	
	int dx_0 = pt_2.x - pt_1.x;		// x2 - x1
	int dx_1 = pt_4.x - pt_3.x;		// x4 - x3
	
	int dy_0 = pt_2.y - pt_1.y;		// y2 - y1
	int dy_1 = pt_4.y - pt_3.y;		// y4 - y3

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
		return FAIL;	// lines does't crossover
	cross.x = pt_1.x + dx_0*t;
	cross.y = pt_1.y + dy_0*t;
	return SUCCESS;
}


int Canvas::getSect(ivec3 pt){
	// bits: 0 - left, 1 - down, 2 - right, 3 - up
	int sect = 0;	 
	if (pt.x < 0)
		sect += 1;
	else if (pt.x >= surface.w)
		sect += 4;
	if (pt.y < 0)
		sect += 2;
	else if (pt.y >= surface.h)
		sect += 8;
	return sect;
}

int Canvas::cutLine(ivec3 &pt_1, ivec3 &pt_2){
	// Cohen–Sutherland algorithm
	
	// sectors
	int sect_1 = getSect(pt_1);
	int sect_2 = getSect(pt_2);

	if (!sect_1 && !sect_2)		// full visible
		return SUCCESS;
	
	if (sect_1 & sect_2)		// full invisible
		return FAIL;
	
	const static ivec3 corners[4] = {		// canvas corners
		ivec3(0, surface.h-1, 1),
		ivec3(0, 0, 1),
		ivec3(surface.w-1, 0, 1),
		ivec3(surface.w-1, surface.h-1, 1)
	};
	static ivec3 cross;
	int cross_count = 0;

	for (int i = 0; i < 4; i++){
		if ((sect_1 | sect_2) & (1 << i)){
			if (!crossPoint(pt_1, pt_2, corners[i], corners[(i+1)%4], cross))
				continue;

			cross_count++;
			if (sect_1 & (1 << i))
				pt_1 = cross;
			else
				pt_2 = cross;
			if (!cutLine(pt_1, pt_2))
				return FAIL;		// theoretically will never happen
		}
	}
	if (!cross_count)
		return FAIL;		// full invisible (different sectors)
	return SUCCESS;			// part visible
}