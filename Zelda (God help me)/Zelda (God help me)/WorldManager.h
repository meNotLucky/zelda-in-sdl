/*

WORLD MANAGER

This system is used for generating and handeling the game world that you play in.
It renders and updates the levels it contains and switches between them seamlessly, just like in the original game.

The levels themselves are generated from a data file which contains data for tthe different tiles.
Each level has its own position in the world, and its own set of enemies.

It was designed like this to easely add and switch between levels during game developement.
With this system, all you need to do is create a data file and call it 'level_[ID]', so for example "level_2.txt".
Then, to add the level into the game, you just have to add it to the world manager using the 'add_level' function,
and give it the same ID as in the name of the data file, specify the type of level, the position and enemies.

*/

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
	~WorldManager();
	void add_level(int p_level_id, LevelType p_level_type, int pos_x, int pos_y, int enemy_amount, EnemyType e_type, bool render_level);
	void switch_level(int current_level_id, int new_level_id, SwitchDirection dir);
	void enter_cave_level(Player* player);
	void exit_cave_level(Player* player);
	bool on_player_death(SDL_Renderer* p_renderer, Player* player);
	void update_world(Player* player);
	void render_world(SDL_Renderer* p_renderer);
	void reset_world(int starting_level);
};