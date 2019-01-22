#include "InputManager.h"

bool InputManager::key_down(SDL_Scancode p_key)
{
	return m_keystrokes.key_down(p_key);
}

bool InputManager::key_pressed(SDL_Scancode p_key)
{
	return m_keystrokes.key_pressed(p_key);
}

bool InputManager::key_released(SDL_Scancode p_key)
{
	return m_keystrokes.key_released(p_key);
}

void InputManager::update_events()
{
	m_keystrokes.update();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EventType::SDL_KEYDOWN)
		{
			m_keystrokes.update_key(event.key.keysym.scancode, true);
		}
		else if (event.type == SDL_EventType::SDL_KEYUP)
		{
			m_keystrokes.update_key(event.key.keysym.scancode, false);
		}
	}
}
