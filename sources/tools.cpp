#include "tools.h"


int lineCrossSurf(vec4 pt_l1, vec4 pt_l2, vec4 pt_s1, vec4 pt_s2, vec4 pt_s3, vec4 &cross){
	// 	Kramer's method for the following equalities:
	//
	//	line:		p_cross = p0 + dp * t
	//	surface:	p_cross = p0 + dp1 * k1 + dp2 * k2
	//
	//	x_cross =  (line)  x1 + (x2-x1)*t  =  (surf)  x1 + (x2-x1)*k1 + (x3-x1)*k2 
	//	y_cross =  (line)  y1 + (y2-y1)*t  =  (surf)  y1 + (y2-y1)*k1 + (y3-y1)*k2
	//	z_cross =  (line)  z1 + (z2-z1)*t  =  (surf)  z1 + (z2-z1)*k1 + (z3-z1)*k2

	float dx_l = pt_l2.x - pt_l1.x;		//	x2-x1	(line)
	float dy_l = pt_l2.y - pt_l1.y;		//	y2-y1
	float dz_l = pt_l2.z - pt_l1.z;		//	z2-z1

	float dx_s1 = pt_s2.x - pt_s1.x;	//	x2-x1	(surf)
	float dy_s1 = pt_s2.y - pt_s1.y;	//	y2-y1
	float dz_s1 = pt_s2.z - pt_s1.z;	//	z2-z1

	float dx_s2 = pt_s3.x - pt_s1.x;	//	x3-x1	(surf)
	float dy_s2 = pt_s3.y - pt_s1.y;	//	y3-y1
	float dz_s2 = pt_s3.z - pt_s1.z;	//	z3-z1

	float dx_sl = pt_s1.x - pt_l1.x;
	float dy_sl = pt_s1.y - pt_l1.y;
	float dz_sl = pt_s1.z - pt_l1.z;

	float det = dx_l*dy_s1*dz_s2 + dx_s1*dy_s2*dz_l + dx_s2*dy_l*dz_s1 - dx_s2*dy_s1*dz_l - dx_s1*dy_l*dz_s2 - dx_l*dy_s2*dz_s1;	// main determinant

	if (!det)
		return FAIL;		// line and surface are parallel

	float det_t = dx_sl*dy_s1*dz_s2 + dx_s1*dy_s2*dz_sl + dx_s2*dy_sl*dz_s1 - dx_s2*dy_s1*dz_sl - dx_s1*dy_sl*dz_s2 - dx_sl*dy_s2*dz_s1;
	// surface is infinite; k1 and k2 is not needed
	// float det_k1 = dx_l*dy_sl*dz_s2 + dx_sl*dy_s2*dz_l + dx_s2*dy_l*dz_sl - dx_s2*dy_sl*dz_l - dx_sl*dy_l*dz_s2 - dx_l*dy_s2*dz_sl;
	// float det_k2 = dx_l*dy_s1*dz_sl + dx_s1*dy_sl*dz_l + dx_sl*dy_l*dz_s1 - dx_sl*dy_s1*dz_l - dx_s1*dy_l*dz_sl - dx_l*dy_sl*dz_s1;

	float t = det_t / det;
	// float k1 = det_k1 / det;
	// float k2 = det_k2 / det;
	if (t < 0 || t > 1)
		return FAIL;

	cross.x = pt_l1.x + dx_l*t;
	cross.y = pt_l1.y + dy_l*t;
	cross.z = pt_l1.z + dz_l*t;

	return SUCCESS;
}


float pointRelateSurf(vec4 pt_1s, vec4 pt_2s, vec4 pt_3s, vec4 pt){

	//	surface equation by three points pt_1, pt_2, pt_3:
	/*
		|x -x1  y -y1  z -z1|
		|x2-x1  y2-y1  z2-z1| = 0
		|x3-x1  y3-y1  y3-y1|
	*/
	//	Common surface equation:
	//	Ax + By + Cz + D = 0

	float dx2 = pt_2s.x - pt_1s.x;	// x2-x1
	float dx3 = pt_3s.x - pt_1s.x;	// x3-x1

	float dy2 = pt_2s.y - pt_1s.y;	// y2-y1
	float dy3 = pt_3s.y - pt_1s.y;	// y3-y1

	float dz2 = pt_2s.z - pt_1s.z;	// z2-z1
	float dz3 = pt_3s.z - pt_1s.z;	// z3-z1

	float A = dy2 * dz3 - dy3 * dz2;
	float B = dz2 * dx3 - dz3 * dx2;
	float C = dx2 * dy3 - dx3 * dy2;
	float D = - pt_1s.x * A - pt_1s.y * B - pt_1s.z * C;

	float position = A * pt.x + B * pt.y + C * pt.z + D;	// >0 -- higher; <0 lower; =0 on it

	return position;
}