#include "camera.h"


ivec3 Camera::projection(vec4 pt){
	mat4 T = mat4{right, up, forward, W_DIR};		// transition matrix to new basis
	vec4 v = pt - position;							// vector in old basis
	vec4 v_new = T * v;								// vector in new basis
	ivec3 proj(v_new[0], v_new[1], 1);				// projection to Oxy surface
	return proj;
}


void Camera::rotate(float angle_Ox, float angle_Oy){
	mat4 mat_rot = MAT4_rot_Ox(angle_Ox) * MAT4_rot_Oy(angle_Oy);
	right = right * mat_rot;
	up = up * mat_rot;
	forward = forward * mat_rot;
}

void Camera::shift(float dx, float dy, float dz){
	position = position * MAT4_shift(dx,dy,dz);
	cout << position.x << " ";
}
