/*

INPUT MANAGER

The Input Manager is used to check for user input sent to the window.
It can check for any keystroke that SDL has a scancode for.

Its main purpouse is to make it easier to check for different types of inputs anywhere in the program,
without having to create a new SDL event in evey file.

*/

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