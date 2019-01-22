#pragma once

#include "KeyStrokes.h"

class InputManager
{
	KeyStrokes m_keystrokes;

public:
	bool key_down(SDL_Scancode p_key);
	bool key_pressed(SDL_Scancode p_key);
	bool key_released(SDL_Scancode p_key);
	void update_events();
};