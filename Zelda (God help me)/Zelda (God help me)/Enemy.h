#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Tile.h"
#include "EnemyProjectile.h"
#include <map>

enum EnemyType {
	WALKING,
	JUMPING
};

enum MovingDirection {
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};

class Enemy : public GameObject {

	EnemyType enemy_type;
	MovingDirection dir;

	int speed_x;
	int speed_y;

	float timer_1;

	int rand;
	int new_move = 1;

	bool can_attack;
	bool can_move;
	bool is_dead;
	bool has_spawned;

	Animation* spawning;
	Animation* anim_up;
	Animation* anim_down;
	Animation* anim_left;
	Animation* anim_right;
	Animation* jumping;
	bool is_moving;

	EnemyProjectile* projectile;
	float proj_cooldown = 0;

public:
	Enemy() {};
	Enemy(int spawn_x, int spawn_y, EnemyType e_type);
	//~Enemy() {
	//	if (m_collider != nullptr) {
	//		delete m_collider;
	//		m_collider = nullptr;
	//	}
	//};
	void render(SDL_Renderer* p_renderer);
	bool get_new_move(MovingDirection move_dir_1, MovingDirection move_dir_2);
	void fire_projectile(MovingDirection dir);
	void update(std::map<int, Tile> p_tiles);
	void update();
	void on_collision(GameObject* p_other);

	void set_active(bool active) { m_active = active; };
	bool is_active() { return m_active; };
	bool enemy_death();
};