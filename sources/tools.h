#pragma once

#include <iostream>
using namespace std;

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

// Affine matrix and vectors
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
#define MAT4_rot_Ox(a)				mat4(1,0,0,0, 0,cos(a),sin(a),0, 0,-sin(a),cos(a),0, 0,0,0,1)	// rotating matrix around Ox axis
#define MAT4_rot_Oy(a)				mat4(cos(a),0,sin(a),0, 0,1,0,0, -sin(a),0,cos(a),0, 0,0,0,1)	// rotating matrix around Ox axis
#define MAT4_rot_Oz(a)				mat4(cos(a),sin(a),0,0, -sin(a),cos(a),0,0, 0,0,1,0, 0,0,0,1)	// rotating matrix around Ox axis

#define VEC3_scale(a)			vec3(a,a,0);
#define VEC4_scale(a)			vec4(a,a,a,0);


// Directions
#define RIGHT					vec4(1,0,0,0)
#define UP						vec4(0,1,0,0)
#define FORWARD					vec4(0,0,1,0)
#define W_DIR					vec4(0,0,0,1)

// Functions
template<length_t N>
void mat_debug(mat<N, N, f32, defaultp> m){		// print matrix members into console
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++)
			cout << m[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

template<length_t N>
void vec_debug(vec<N, float, defaultp> v){		// print vector members into console
	for (int i = 0; i < N; i++)
		cout << v[i] << " ";
	cout << endl;
}

template<typename T>
void bits_debug(T num){
	int N = sizeof(T)*8;
	cout << N << endl;
	for (int i = N-1; i >= 0; i--){
		cout << (bool(num & 1 << i));
	}
	cout << endl;
}


int lineCrossSurf(vec4 pt_l1, vec4 pt_l2, vec4 pt_s1, vec4 pt_s2, vec4 pt_s3, vec4 &cross);


float pointRelateSurf(vec4 pt_1s, vec4 pt_2s, vec4 pt_3s, vec4 pt);		// find point position around a surface (three vec4)

