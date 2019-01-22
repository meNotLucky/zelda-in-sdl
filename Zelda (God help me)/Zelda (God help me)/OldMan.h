#pragma once
#include "GameObject.h"

class OldMan : public GameObject {
public:
	OldMan() {};
	OldMan(int p_x, int p_y);
	void render(SDL_Renderer* p_renderer);
	void update();
};