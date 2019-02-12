#include "WorldManager.h"
#include "Service.h"
#include "CollisionManager.h"

WorldManager::WorldManager(int starting_level) {

	current_level = starting_level;
	do_switch = false;
}

WorldManager::~WorldManager()
{
	for (auto it = levels.begin(); it != levels.end(); it++) {
		it->second.delete_level();
		levels.erase(it);
	}
}

void WorldManager::add_level(int p_level_id, LevelType p_level_type, int pos_x, int pos_y, int enemy_amount, EnemyType e_type, bool render_level)
{
	Level new_level(p_level_id, p_level_type, pos_x, pos_y, enemy_amount, e_type, render_level);
	levels[p_level_id] = new_level;
}

void WorldManager::switch_level(int current_level_id, int new_level_id, SwitchDirection dir)
{
	levels[current_level].despawn_enemies();
	levels[current_level].disable_hitboxes(true);
	levels[current_level].check_collisions(false);

	switch_dir = dir;
	do_switch = true;
	current_level = new_level_id;
}

void WorldManager::enter_cave_level(Player* player)
{
	levels[current_level].set_render_level(false);
	current_level = 5;
	levels[current_level].set_render_level(true);
}

void WorldManager::exit_cave_level(Player* player)
{
	levels[current_level].set_render_level(false);
	current_level = 1;
	levels[current_level].set_render_level(true);
	player->exit_cave();
}

bool WorldManager::on_player_death(SDL_Renderer* p_renderer, Player * player)
{
	levels[current_level].despawn_enemies();
	render_world(p_renderer);
	if(player->animation_finished())
		return true;

	return false;
}

void WorldManager::update_world(Player* player)
{
	if (!do_switch) {

		levels[current_level].check_collisions(true);

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
		else if (current_level == 5) {
			if (player->get_pos_y() > 960 - player->get_collider()->get_bounds().h)
				exit_cave_level(player);
			if (player->get_pos_y() < 580)
				player->set_pos(player->get_pos_x(), 580);
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

	levels[current_level].update_level(player);

}

void WorldManager::render_world(SDL_Renderer* p_renderer)
{
	for (auto it = levels.begin(); it != levels.end(); it++) {
			it->second.render_level(p_renderer);
	}
}

void WorldManager::reset_world(int starting_level)
{
	current_level = starting_level;
	do_switch = false;
}
