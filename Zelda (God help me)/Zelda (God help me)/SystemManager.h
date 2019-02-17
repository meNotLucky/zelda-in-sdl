/*

SYSTEM MANAGER

The system manager is a simple handler to create the game window and initialize all of the SDL systems.
It also checks for the 'SDL_Quit' event.

The purpouse of this system is mainly to make the 'main.cpp' file less cluttered and easier to read.

*/

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