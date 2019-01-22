#pragma once

#include <iostream>
#include "FSM.h"
#include "Sprite.h"
#include "AudioManager.h"

class Death : public State {

	SDL_Renderer* m_renderer;

	Music* m_music;
	SDL_Rect m_screen_rect;
	Sprite* m_end_screen;

public:
	Death(SDL_Renderer* p_renderer);
	void enter();
	void exit();
	bool update();
};