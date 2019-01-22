#include "KeyStrokes.h"

KeyStrokes::KeyStrokes()
{
	for (int i = 0; i < SDL_Scancode::SDL_NUM_SCANCODES; i++)
	{
		lastFrame[i] = 0;
		currentFrame[i] = 0;
	}
}

void KeyStrokes::update() {
	for (int i = 0; i < SDL_Scancode::SDL_NUM_SCANCODES; i++)
	{
		lastFrame[i] = currentFrame[i];
	}
}

bool KeyStrokes::key_down(SDL_Scancode p_key)
{
	return currentFrame[p_key];
}

bool KeyStrokes::key_pressed(SDL_Scancode p_key)
{
	return (lastFrame[p_key] == false && currentFrame[p_key] == true);
}

bool KeyStrokes::key_released(SDL_Scancode p_key)
{
	return (lastFrame[p_key] == true && currentFrame[p_key] == false);
}

void KeyStrokes::update_key(SDL_Scancode p_key, bool p_value)
{
	currentFrame[p_key] = p_value;
}
