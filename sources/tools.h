#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

// Status
#define SUCCESS 	1
#define FAIL 		0

// Colors
#define CL_RED 		0xff0000
#define CL_GREEN 	0x00ff00
#define CL_BLUE 	0x0000ff
#define CL_CYAN 	0x00ffff
#define CL_MAGENTA	0xff00ff
#define CL_YELLOW 	0xffff00
#define CL_WHITE 	0xffffff
#define CL_BLACK 	0x000000

// Affine matrix
#define MAT3_EYE				imat3(1,0,0, 0,1,0, 0,0,1)						// eye matrix
#define MAT3_mir_Ox 			imat3(1,0,0, 0,-1,0, 0,0,1)						// mirroring mftrix on the Ox axis (-)
#define MAT3_mir_Oy 			imat3(-1,0,0, 0,1,0, 0,0,1)						// mirroring mftrix on the Oy axis (|)
#define MAT3_mir_xy 			imat3(0,1,0, 1,0,0, 0,0,1)						// mirroring mftrix on the xy axis (/)
#define MAT3_mir_mxy 			imat3(0,1,0, 1,0,0, 0,0,1)						// mirroring mftrix on the -xy axis (\)
#define MAT3_shift(dx, dy)		imat3(1,0,dx, 0,1,dy, 0,0,1)					// transporting matrix to the (dx, dy) local cords
#define MAT3_rot_clw(a)			mat3(cos(a),sin(a),1, cos(a),-sin(a),1, 0,0,1)	// rotating matrix clockwise (↻)
#define MAT3_rot_ctclw(a) 		mat3(cos(a),-sin(a),1, cos(a),sin(a),1, 0,0,1)	// rotating matrix counterclockwise (↺)
#define MAT3_T(m)				imat3(m[0][0],m[1][0],m[2][0], m[0][1],m[1][1],m[2][1], m[0][2],m[1][2],m[2][2]);	// transpose matrix

#define MAT4_EYE					mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1)	// eye matrix
#define MAT4_shift(dx, dy, dz)		mat4(1,0,0,dx, 0,1,0,dy, 0,0,1,dz, 0,0,0,1)	// transporting matrix to the (dx, dy) local cords

// Directions
#define FORWARD					vec4(0,0,0,1)
#define UP						vec4(0,0,-1,0)
#define RIGHT					vec4(0,1,0,0)