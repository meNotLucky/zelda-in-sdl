#pragma once

#include <SDL.h>

class KeyStrokes {
	bool currentFrame[SDL_Scancode::SDL_NUM_SCANCODES];
	bool lastFrame[SDL_Scancode::SDL_NUM_SCANCODES];

public:
	KeyStrokes();
	~KeyStrokes() {};
	void update();
	bool key_down(SDL_Scancode p_key);
	bool key_pressed(SDL_Scancode p_key);
	bool key_released(SDL_Scancode p_key);
	void update_key(SDL_Scancode p_key, bool p_value);
};