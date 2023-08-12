#include <iostream>
using namespace std;

#include <SDL.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "tools.h"
#include "smartArray.h"

#include "canvas.h"
#include "camera.h"


class Scene{

	public:

	Scene(Canvas canvas){
		Camera camera();
	}
	~Scene(){}
};