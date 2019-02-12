#pragma once

#include "GameObject.h"

class Sword : public GameObject {

public:
	Sword() {};
	Sword(int p_x, int p_y);
	~Sword() { if (m_collider != nullptr) { delete m_collider; m_collider = nullptr; } };
	void render(SDL_Renderer* p_renderer);
	void update();
};