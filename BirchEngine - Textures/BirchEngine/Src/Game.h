#pragma once

#include "SDL.h"
#include <iostream>
#include "SDL_image.h"
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Rect camera;
private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window *window;
	
	SDL_Texture * fondo;
	int generateX;
	int generateY;
	
};