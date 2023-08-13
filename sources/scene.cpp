#include "scene.h"


void Scene::update(){
	// canvas.update();
	// drawObj(cube);
	drawObj(cube);
	// cube;

}


ivec3 Scene::projection(vec4 pt){
	return ivec3(pt.x, pt.y, 0);
}


void Scene::drawObj(Object &obj){

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			cout << obj.matrix[i][j] << " ";
	cout << endl;

	for (int i = 0; i < obj.connections.size; i++){
		for (int j = 0; j < 3; j++){
			vec4 pt_1 = obj.points[obj.connections[i][j]] * obj.matrix;
			vec4 pt_2 = obj.points[obj.connections[i][(j+1)%3]] * obj.matrix;
			canvas.drawLine(projection(pt_1), projection(pt_2), CL_RED);
		}
	}
}