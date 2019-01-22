#pragma once

#include "GameObject.h"

class Sword : public GameObject {

public:
	Sword() {};
	Sword(int p_x, int p_y);
	void render(SDL_Renderer* p_renderer);
	void update();
};