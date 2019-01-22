#pragma once

#include "GameObject.h"
#include "Sword.h"
#include "Animation.h"
#include "AudioManager.h"

enum LastDirection {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Player : public GameObject {

	// Properties
	int m_health;
	float speed_x;
	float speed_y;

	// Checks
	bool aquired_sword;
	bool can_attack;
	bool is_attacking;
	bool is_immune;
	bool can_move;
	bool is_moving;
	bool going_down;
	bool going_up;
	bool is_dead;
	bool anim_finished;
	bool death_sound_played;

	// Animations
	Animation* anim_up;
	Animation* anim_down;
	Animation* anim_left;
	Animation* anim_right;
	Animation* anim_going_down;
	Animation* anim_going_up;
	Animation* anim_aquire_sword;
	Animation* anim_atk_up;
	Animation* anim_atk_down;
	Animation* anim_atk_left;
	Animation* anim_atk_right;
	Animation* anim_death;

	// Sounds
	Sound* sound_sword_slash;
	Sound* sound_sword_shoot;
	Sound* sound_shield;
	Sound* sound_hurt;
	Sound* sound_die;
	Sound* sound_get_heart;
	Sound* sound_low_health;
	Sound* sound_get_rupee;
	Sound* sound_stairs;
	Sound* sound_aquire_sword;

	float timer = 0;
	LastDirection last_dir;

public:
	Player();
	void render(SDL_Renderer* p_renderer);
	void update();
	void move_rect(int x, int y);
	void exit_cave() { going_up = true; sound_stairs->play_sound(0); };
	void enable_movement(bool disable) { can_move = disable; };
	void on_collision(GameObject* p_other);
	bool player_attacking() { return is_attacking; };
	bool player_death();
	void reset_player();

	int get_health() { return m_health; };
	bool get_sword() { return aquired_sword; };
	SDL_Rect get_rect() { return m_rect; };
	Animation* death_anim() { return anim_death; };
	bool animation_finished() { return anim_finished; };
};