#pragma once
#include "GameObject.h"
#include "Animation.h"

class Fire : public GameObject {

	Animation* m_anim;

public:
	Fire() {};
	Fire(int p_x, int p_y);
	void render(SDL_Renderer* p_renderer);
	void update();
};