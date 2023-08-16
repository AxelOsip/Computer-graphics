#include "window.h"

int Window::init(){

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return FAIL;

	ptrWindow = SDL_CreateWindow(header, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution.x, resolution.y, SDL_WINDOW_SHOWN);
	if (ptrWindow == NULL)
		return FAIL;

	ptrRenderer = SDL_CreateRenderer(ptrWindow, -1, SDL_RENDERER_SOFTWARE);
	if (ptrRenderer == NULL)
		return FAIL;

	ptrSurface = SDL_CreateRGBSurface(0, resolution.x, resolution.y, 32,
										0x00FF0000,  // R
										0x0000FF00,  // G
										0x000000FF,  // B
										0x00000000); // alpha

	ptrTexture = SDL_CreateTextureFromSurface(ptrRenderer, ptrSurface);
	if (ptrTexture == NULL)
		return FAIL;

	SDL_SetRenderDrawColor(ptrRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	canvas.setSurface(*ptrSurface);
	scene.setCanvas(canvas);

	return SUCCESS;
};


void Window::close()
{
	SDL_DestroyTexture(ptrTexture);
	SDL_DestroyRenderer(ptrRenderer);
	SDL_DestroyWindow(ptrWindow);

	ptrTexture = NULL;
	ptrRenderer = NULL;
	ptrWindow = NULL;
	SDL_Quit();
}


void Window::event(bool* quit){
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0){
		if (event.type == SDL_QUIT){
			*quit = true;
			return;
		}
		if (event.type == SDL_KEYDOWN){
			int key = event.key.keysym.scancode;
			scene.control(key);
		}
	}
}


void Window::loop(){
	bool quit = false;
	while (!quit){	
		uint32 start = SDL_GetTicks();

		event(&quit);
		SDL_RenderClear(ptrRenderer);

		scene.update();			// 3D-dimension
		// canvas.update();		// 2D-dimension

		SDL_UpdateTexture(ptrTexture, NULL, ptrSurface->pixels, ptrSurface->pitch);
		SDL_RenderCopy(ptrRenderer, ptrTexture, NULL, NULL);
		SDL_RenderPresent(ptrRenderer);

		if (1000.f/FPS > SDL_GetTicks() - start)
			SDL_Delay(1000.f/FPS - SDL_GetTicks() + start);
	}
}
