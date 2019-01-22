#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>

class SystemManager {
public:

	bool running;
	bool quit_event;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event events;

	SystemManager();
	~SystemManager();
	void init_system();
	void update();
};