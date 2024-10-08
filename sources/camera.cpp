#include "camera.h"


ivec3 Camera::projection(vec4 pt){
	mat4 T = mat4{right, -up, forward, W_DIR};		// transition matrix to new basis
	vec4 v = pt - position;	// vector in old basis
	vec4 v_new = v * T;								// vector in new basis
	vec4 focus = this->focus * T;

	float ratio = -focus.z / (-focus.z + v_new.z);	// perspective projection ratio
	float x_new = v_new.x * ratio * resolution.x;
	float y_new = v_new.y * ratio * resolution.y;

	ivec3 proj(x_new+center.x, y_new+center.y, 1);
	// ivec3 proj(v_new[0]+center.x, v_new[1]+center.y, 1);			// orthogonal projection to local Oxy surface
	return proj;
}


uint8 Camera::getSect(vec4 pt){
	// bits: 0 - left, 1 - down, 2 - right, 3 - up, 4 - back

	vec4 scale = VEC4_scale(0.5);
	vec4 corners[4] = {		// canvas corners with camera position and orientation
		position - right*scale - up*scale,
		position - right*scale + up*scale,
		position + right*scale + up*scale,
		position + right*scale - up*scale
	};

	uint8 sect = 0;

	// checking truncated piramide sides
	for (int i = 0; i < 4; i++){
		if (pointRelateSurf(corners[i], corners[(i+1)%4], position + focus, pt) > 0)
			sect += 1 << i;
	}
	// checking truncated piramide up
	if(pointRelateSurf(corners[0], corners[1], corners[2], pt) > 0)
		sect += 1 << 4;

	return sect;
}

int Camera::cutLine(vec4 &pt_1, vec4 &pt_2){
	
	uint8 sect_1 = getSect(pt_1);
	uint8 sect_2 = getSect(pt_2);
	
	if (!sect_1 && !sect_2)		// full visible
		return SUCCESS;
	
	if (sect_1 & sect_2)		// full invisible
		return FAIL;
	
	vec4 scale = VEC4_scale(0.5);
	vec4 corners[4] = {			// canvas corners with camera position and orientation
		position - right*scale - up*scale,
		position - right*scale + up*scale,
		position + right*scale + up*scale,
		position + right*scale - up*scale
	};

	static vec4 cross;
	int cross_count = 0;

	// cutting by truncated piramide sides
	for (int i = 0; i < 4; i++){
		if (!(sect_1 | sect_2) & (1 << i))
			continue;
		if (!lineCrossSurf(pt_1, pt_2, corners[i], corners[(i+1)%4], position + focus, cross))
			continue;

		cross_count++;
		if (sect_1 & (1 << i))
			pt_1 = cross;
		else
			pt_2 = cross;
	}

	// cutting by truncated piramide up
	int status = SUCCESS;
	if (!(sect_1 | sect_2) & (1 << 4))
		status = FAIL;
	if (!lineCrossSurf(pt_1, pt_2, corners[0], corners[1], corners[2], cross))
		status = FAIL;

	if (status){
		cross_count++;
		if (sect_1 & (1 << 4))
			pt_1 = cross;
		else
			pt_2 = cross;
	}

	if (!cross_count){
		return FAIL;		// full invisible (different sectors)
	}
	return SUCCESS;			// part visible
}


int Camera::cutSurface(Array<vec4> &surface){
	
	static Array<uint8> sectors{0};
	uint8 full_visible = 0;		// 00000000
	uint8 full_invisible = 31;	// 00011111
	int cross_count = 0;
	vec4 cross;

	vec4 scale = VEC4_scale(0.5);
	vec4 corners[4] = {			// canvas corners with camera position and orientation
		position - right*scale - up*scale,
		position - right*scale + up*scale,
		position + right*scale + up*scale,
		position + right*scale - up*scale
	};

	for (int i = 0; i < surface.size; i++){
		uint8 sect = getSect(surface[i]);
		sectors[i] = sect;
		full_visible = !full_visible && !sect;
		full_invisible = full_invisible & sect;
		// bits_debug(sect);
	}
	

	if (full_visible)			// full visible
		return SUCCESS;
	
	if (full_invisible)			// full invisible
		return FAIL;

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < surface.size; j++){
			int k = (j+1)%surface.size;
			
			if (!(sectors[j] | sectors[k]) & (1 << i))
				continue;

			if (lineCrossSurf(surface[j], surface[k], corners[i], corners[(i+1)%4], position + focus, cross))
				cross_count++;
		}
	}

	if (!cross_count)
		return FAIL;			// full invisible (different sectors)

	return SUCCESS;				// part visible
}


void Camera::rotate_hor(float angle){
	// rotate arond global Oy
	Quaternion q(vec4(0,1,0,0), angle);

	right = (q * Quaternion(right) * ~q).getVector();
	up = (q * Quaternion(up) * ~q).getVector();
	forward = (q * Quaternion(forward) * ~q).getVector();
	focus = (q * Quaternion(focus) * ~q).getVector();
}

void Camera::rotate_vert(float angle){
	// rotate arond local Ox
	Quaternion q(right, angle);

	up = (q * Quaternion(up) * ~q).getVector();
	forward = (q * Quaternion(forward) * ~q).getVector();
	focus = (q * Quaternion(focus) * ~q).getVector();
}


void Camera::shift(float dx, float dy, float dz){
	vec4 move_right(right.x, 0, right.z, 0);
	vec4 move_up(0, 1, 0, 0);
	vec4 move_forward = normalize(vec4(forward.x, 0, forward.z, 0));
	position = position + move_right*dx + move_up*dy + move_forward*dz;
}
