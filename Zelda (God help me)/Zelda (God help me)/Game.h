#pragma once

#include <iostream>
#include "FSM.h"
#include "Sprite.h"
#include "Animation.h"
#include "SpriteManager.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "WorldManager.h"
#include "Player.h"
#include "UserInterface.h"

class Game : public State {

	Music* m_music;
	SDL_Renderer* m_renderer;
	Player player;

	UsierInterface* m_ui;
	SDL_Rect ui_background;

public:
	Game(SDL_Renderer* p_renderer);
	void enter();
	void exit();
	bool update();
};