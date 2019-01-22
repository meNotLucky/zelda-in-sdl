#pragma once

#include <iostream>
#include "FSM.h"
#include "Sprite.h"
#include "Animation.h"
#include "SpriteManager.h"
#include "AudioManager.h"
#include "InputManager.h"

class Menu : public State {

	SDL_Renderer* m_renderer;

	// Animations
	Animation* title_animation;
	Sprite* title_still;
	SDL_Rect title_rect;

	Sprite* story_items;
	SDL_Rect story_rect;

	Animation* waterfall_animation;
	SDL_Rect waterfall_rect;

	// Timing related
	float timer = 0;
	int r = 255; int g = 255; int b = 255;
	float story_y = 960;

	// Music
	Music* intro_music;

public:
	Menu(SDL_Renderer* p_renderer);
	void enter();
	void exit();
	bool update();
};