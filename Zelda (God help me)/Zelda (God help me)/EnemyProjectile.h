#pragma once

#include "GameObject.h"

enum FireDirection {
	FIRE_UP,
	FIRE_DOWN,
	FIRE_LEFT,
	FIRE_RIGHT
};

class EnemyProjectile : public GameObject {

	int m_speed;
	FireDirection fire_dir;

public:
	EnemyProjectile() {};
	EnemyProjectile(int p_x, int p_y, FireDirection p_dir);
	~EnemyProjectile() { if (m_collider != nullptr) { delete m_collider; m_collider = nullptr; } };
	void render(SDL_Renderer* p_renderer);
	void update();
};