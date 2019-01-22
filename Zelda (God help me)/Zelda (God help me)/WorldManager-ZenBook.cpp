#include "WorldManager.h"
#include "Service.h"
#include "CollisionManager.h"

#include <iostream>

WorldManager::WorldManager(int starting_level) {

	current_level = starting_level;
	do_switch = false;
}

void WorldManager::add_level(int p_level_id, int pos_x, int pos_y, int enemy_amount)
{
	Level new_level(p_level_id, pos_x, pos_y, enemy_amount);
	levels[p_level_id] = new_level;
}

void WorldManager::switch_level(int current_level_id, int new_level_id, SwitchDirection dir)
{
	levels[current_level].despawn_enemies();
	levels[current_level].disable_hitboxes(true);

	switch_dir = dir;
	do_switch = true;
	current_level = new_level_id;
}

void WorldManager::update(Player* player)
{
	if (!do_switch) {

		if (current_level == 1) {
			if (player->get_pos_x() < 0)
				switch_level(1, 3, SWITCH_LEFT);
			if (player->get_pos_x() + player->get_collider()->get_bounds().w > 1024)
				switch_level(1, 2, SWITCH_RIGHT);
			if (player->get_pos_y() < 256)
				switch_level(1, 4, SWITCH_UP);
		}
		else if (current_level == 2) {
			if (player->get_pos_x() < 0 - player->get_collider()->get_bounds().w)
				switch_level(2, 1, SWITCH_LEFT);
			if (player->get_pos_x() > 1024 - player->get_collider()->get_bounds().w)
				player->set_pos(1024 - player->get_collider()->get_bounds().w, player->get_pos_y());
			if (player->get_pos_y() < 256)
				player->set_pos(player->get_pos_x(), 256);
		}
		else if (current_level == 3) {
			if (player->get_pos_x() > 1024)
				switch_level(3, 1, SWITCH_RIGHT);
			if (player->get_pos_x() < 0)
				player->set_pos(0, player->get_pos_y());
			if (player->get_pos_y() < 256)
				player->set_pos(player->get_pos_x(), 256);
		}
		else if (current_level == 4) {
			if (player->get_pos_y() > 960)
				switch_level(4, 1, SWITCH_DOWN);
			if (player->get_pos_x() < 0)
				player->set_pos(0, player->get_pos_y());
			if (player->get_pos_x() > 1024 - player->get_collider()->get_bounds().w)
				player->set_pos(1024 - player->get_collider()->get_bounds().w, player->get_pos_y());
		}
	}

	if (do_switch) {

		timer += 1.0f / 60;

		for (auto it = levels.begin(); it != levels.end(); it++) {
			it->second.move_level(switch_dir);
		}

		player->enable_movement(false);

		if (switch_dir == SWITCH_UP) {
			if (player->get_pos_y() < 960 - player->get_collider()->get_bounds().h * 2)
				player->move_rect(0, 8);
		}
		if (switch_dir == SWITCH_DOWN) {
			if (player->get_pos_y() > 256)
				player->move_rect(0, -8);
		}
		if (switch_dir == SWITCH_LEFT) {
			if (player->get_pos_x() < 960)
				player->move_rect(8, 0);
		}
		if (switch_dir == SWITCH_RIGHT) {
			if (player->get_pos_x() > 10)
				player->move_rect(-8, 0);
		}


		if (switch_dir == SWITCH_LEFT || switch_dir == SWITCH_RIGHT) {
			if (timer >= 2.12f) {
				timer = 0;
				do_switch = false;
				levels[current_level].disable_hitboxes(false);
				levels[current_level].spawn_enemies();
				player->enable_movement(true);
			}
		}
		else if (switch_dir == SWITCH_UP || switch_dir == SWITCH_DOWN) {
			if (timer >= 1.46f) {
				timer = 0;
				do_switch = false;
				levels[current_level].disable_hitboxes(false);
				levels[current_level].spawn_enemies();
				player->enable_movement(true);
			}
		}
	}

	std::map<int, Tile> level_tiles = get_tiles();
	std::map<int, Tile*> coll_tiles;
	std::map<int, Enemy> enemies = levels[current_level].get_enemies();
	int n = 0;

	for (auto it = level_tiles.begin(); it != level_tiles.end(); it++) {
		if (it->second.get_collider() != nullptr) {
			coll_tiles[n] = &it->second;
			n++;
		}
	}
	for (int i = 0; i < coll_tiles.size(); i++) {
		Collider* coll_b = coll_tiles[i]->get_collider();
		for (auto it = enemies.begin(); it != enemies.end(); it++) {
			if (Service<CollisionManager>::Get()->check_collision(it->second.get_collider(), coll_b)) {
				it->second.on_collision(coll_tiles[i]);
			}
		}
	}

}

void WorldManager::render_world(SDL_Renderer* p_renderer)
{
	for (auto it = levels.begin(); it != levels.end(); it++) {
			it->second.render_level(p_renderer);
	}
}

std::map<int, Tile> WorldManager::get_tiles()
{
	return levels[current_level].get_tiles();
}
