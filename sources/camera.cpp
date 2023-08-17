#include "camera.h"


ivec3 Camera::projection(vec4 pt){
	mat4 T = mat4{right, -up, forward, W_DIR};		// transition matrix to new basis
	vec4 v = pt - position;	// vector in old basis
	vec4 v_new = v * T;								// vector in new basis

	float ratio = -focus.z / (-focus.z + v_new.z);	// perspective projection ratio
	float x_new = v_new.x * ratio;
	float y_new = v_new.y * ratio;

	ivec3 proj(x_new+center.x, y_new+center.y, 1);
	// ivec3 proj(v_new[0], v_new[1], 1);			// orthogonal projection to local Oxy surface
	return proj;
}


void Camera::rotate_hor(float angle){
	// rotate arond global Oy
	Quaternion q(vec4(0,1,0,0), -angle);

	right = (q * Quaternion(right) * ~q).getVector();
	up = (q * Quaternion(up) * ~q).getVector();
	forward = (q * Quaternion(forward) * ~q).getVector();
	focus = (q * Quaternion(focus) * ~q).getVector();
}

void Camera::rotate_vert(float angle){
	// rotate arond local Ox
	Quaternion q(right, -angle);

	up = (q * Quaternion(up) * ~q).getVector();
	forward = (q * Quaternion(forward) * ~q).getVector();
	focus = (q * Quaternion(focus) * ~q).getVector();
}


void Camera::shift(float dx, float dy, float dz){
	vec4 move_right(right.x, 0, right.z, 0);
	vec4 move_up(0, 1, 0, 0);
	vec4 move_forward(forward.x, 0, forward.z, 0);
	position = position + move_right*dx + move_up*dy + move_forward*dz;
}
