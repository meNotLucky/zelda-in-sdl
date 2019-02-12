#pragma once

#include <map>
#include "Tile.h"
#include "Enemy.h"
#include "Player.h"
#include "Fire.h"
#include "OldMan.h"
#include "Sword.h"

enum SwitchDirection {
	SWITCH_UP,
	SWITCH_DOWN,
	SWITCH_LEFT,
	SWITCH_RIGHT
};

enum LevelType {
	LEVEL_OVERWORLD,
	LEVEL_CAVE
};

class Level {

	int level_id;
	LevelType level_type;
	int pos_x, pos_y;

	bool do_render_level;
	bool check_collision;

	Fire* fire_1;
	Fire* fire_2;
	OldMan* old_man;
	Sprite* text;
	SDL_Rect text_rect;
	Sword* sword;

	std::map<int, Tile> tiles;
	std::map<int, Enemy> enemies;

public:
	Level() {};
	Level(int p_level_id, LevelType p_level_type, int pos_x, int pos_y, int enemy_amount, EnemyType e_type, bool p_render_level);
	void spawn_enemies();
	Tile* create_spawn_point();
	void despawn_enemies();
	void move_level(SwitchDirection dir);
	void set_render_level(bool p_render) { do_render_level = p_render; };
	void render_level(SDL_Renderer* p_renderer);
	void update_level(Player* player);
	void disable_hitboxes(bool disable);
	void check_collisions(bool check) { check_collision = check; };
	void delete_level();
};