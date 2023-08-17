#include "camera.h"


ivec3 Camera::projection(vec4 pt){
	mat4 T = mat4{right, up, forward, W_DIR};		// transition matrix to new basis
	vec4 v = pt - position;							// vector in old basis
	vec4 v_new = T * v;								// vector in new basis
	ivec3 proj(v_new[0], v_new[1], 1);				// projection to Oxy surface
	return proj;
}


void Camera::rotate_hor(float angle){
	// rotate arond global Oy
	Quaternion q(vec4(0,1,0,0), angle);

	right = (q * Quaternion(right) * ~q).getVector();
	up = (q * Quaternion(up) * ~q).getVector();
	forward = (q * Quaternion(forward) * ~q).getVector();
}

void Camera::rotate_vert(float angle){
	// rotate arond local Ox
	Quaternion q(right, angle);

	up = (q * Quaternion(up) * ~q).getVector();
	forward = (q * Quaternion(forward) * ~q).getVector();
}


void Camera::shift(float dx, float dy, float dz){
	position = position + right*dx + up*dy + forward*dz;
}
