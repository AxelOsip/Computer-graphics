#include "scene.h"


void Scene::update(){
	canvas.update();

	drawObj(cube);

	// vec_debug(camera.up);
	// vec_debug(camera.forward);
	// cout << endl;

}


void Scene::control(int key){
	// keyboard event
	if (key == SDL_SCANCODE_W)
		camera.shift(0, 0, step);
	else if (key == SDL_SCANCODE_S)
		camera.shift(0, 0, -step);
	if (key == SDL_SCANCODE_A)
		camera.shift(-step, 0, 0);
	else if (key == SDL_SCANCODE_D)
		camera.shift(step, 0, 0);
	if (key == SDL_SCANCODE_SPACE)
		camera.shift(0, step, 0);
	else if (key == SDL_SCANCODE_C)
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
			canvas.drawLine(projection(pt_1), projection(pt_2), CL_RED);
		}
	}
}