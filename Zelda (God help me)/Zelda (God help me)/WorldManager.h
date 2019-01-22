#pragma once

#include <map>
#include <fstream>
#include "Level.h"
#include "Player.h"


class WorldManager {

	float timer;
	
	std::map<int, Level> levels;
	int current_level;

	bool do_switch;
	SwitchDirection switch_dir;

public:
	WorldManager() {};
	WorldManager(int starting_level);
	void add_level(int p_level_id, LevelType p_level_type, int pos_x, int pos_y, int enemy_amount, EnemyType e_type, bool render_level);
	void switch_level(int current_level_id, int new_level_id, SwitchDirection dir);
	void enter_cave_level(Player* player);
	void exit_cave_level(Player* player);
	bool on_player_death(SDL_Renderer* p_renderer, Player* player);
	void update_world(Player* player);
	void render_world(SDL_Renderer* p_renderer);
	void reset_world(int starting_level);
};