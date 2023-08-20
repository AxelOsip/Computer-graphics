#include "scene.h"


void Scene::update(){
	canvas.update();

	drawObj(cube);

	vec4 pt_1(0,0, 1, 2);
	vec4 pt_2(0.5,0.5, 3, 1);	

	if (camera.cutLine(pt_1, pt_2)){
		ivec3 proj_1 = camera.projection(pt_1);
		ivec3 proj_2 = camera.projection(pt_2);

		canvas.drawLine(proj_1, proj_2, CL_YELLOW);
		canvas.drawCircle(proj_1, 10, CL_GREEN);
		canvas.drawCircle(proj_2, 10, CL_GREEN);
	}
}


void Scene::control(const uint8 *keys){
	// keyboard event
	if (keys[SDL_SCANCODE_W])
		camera.shift(0, 0, step);
	if (keys[SDL_SCANCODE_S])
		camera.shift(0, 0, -step);
	if (keys[SDL_SCANCODE_A])
		camera.shift(-step, 0, 0);
	if (keys[SDL_SCANCODE_D])
		camera.shift(step, 0, 0);
	if (keys[SDL_SCANCODE_SPACE])
		camera.shift(0, step, 0);
	if (keys[SDL_SCANCODE_C])
		camera.shift(0, -step, 0);
}


void Scene::control(int x, int y){
	// mouse motion event
	camera.rotate_hor(x*sensitivity);
	camera.rotate_vert(y*sensitivity);
}


ivec3 Scene::projection(vec4 pt){
	return camera.projection(pt);
	// return ivec3(pt.x, pt.y, 0);
}


void Scene::drawObj(Object &obj){
	for (int i = 0; i < obj.connections.size; i++){
		for (int j = 0; j < 3; j++){
			vec4 pt_1 = obj.points[obj.connections[i][j]] * obj.matrix;
			vec4 pt_2 = obj.points[obj.connections[i][(j+1)%3]] * obj.matrix;
			if (!camera.cutLine(pt_1, pt_2))
				continue;
			canvas.drawCircle(projection(pt_1), 5, CL_GREEN);
			canvas.drawCircle(projection(pt_2), 5, CL_GREEN);
			canvas.drawLine(projection(pt_1), projection(pt_2), CL_RED);
		}
	}
}