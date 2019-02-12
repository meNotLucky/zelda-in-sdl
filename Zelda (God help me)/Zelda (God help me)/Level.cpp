#include "Level.h"
#include "Service.h"
#include "CollisionManager.h"
#include "SpriteManager.h"
#include <fstream>
#include <string>
#include <iostream>

Level::Level(int p_level_id, LevelType p_level_type, int pos_x, int pos_y, int enemy_amount, EnemyType e_type, bool p_render_level)
{
	level_id = p_level_id;
	level_type = p_level_type;
	int tile_pos_x = pos_x;
	int tile_pos_y = pos_y;

	do_render_level = p_render_level;
	check_collision = true;


	if (level_type == LEVEL_CAVE) {
		fire_1 = new Fire(295, 520);
		fire_2 = new Fire(655, 520);
		old_man = new OldMan(475, 520);
		sword = new Sword(493, 625);
		SDL_Color color = { 255, 255, 255 };
		text_rect.x = 150; text_rect.y = 420; text_rect.w = 715; text_rect.h = 20;
		text = Service<SpriteManager>::Get()->create_text("Assets/Fonts/zelda_nes_font.ttf", "It's dangerous to go alone! Take this.", color, 0, 0, 1075, 30);
	}

	for (int i = 0; i < enemy_amount; i++) {
		Enemy enemy(0, 0, e_type);
		enemies[i] = enemy;
	}

	TileType data[176];
	std::string f_path = "Data/level_" + std::to_string(p_level_id) + ".txt";

	std::ifstream in;
	in.open(f_path.c_str());

	std::string element;
	if (in.is_open()) {
		int i = 0;
		while (in >> element) {
			if (element == "GROUND,")
				data[i] = GROUND;
			if (element == "FOREST,")
				data[i] = FOREST;
			if (element == "FOREST_TOP,")
				data[i] = FOREST_TOP;
			if (element == "FOREST_CORNER_1,")
				data[i] = FOREST_CORNER_1;
			if (element == "FOREST_CORNER_2,")
				data[i] = FOREST_CORNER_2;
			if (element == "FOREST_CORNER_3,")
				data[i] = FOREST_CORNER_3;
			if (element == "FOREST_CORNER_4,")
				data[i] = FOREST_CORNER_4;
			if (element == "TREE,")
				data[i] = TREE;
			if (element == "BUSH,")
				data[i] = BUSH;
			if (element == "CAVE,")
				data[i] = CAVE;
			if (element == "CAVE_GROUND,")
				data[i] = CAVE_GROUND;
			if (element == "CAVE_WALL,")
				data[i] = CAVE_WALL;
			if (element == "CAVE_WALL_TOP,")
				data[i] = CAVE_WALL_TOP;
			i++;
		}
	}

	in.close();

	for (int i = 0; i < 176; i++) {
		
		Tile tile(data[i], tile_pos_x, tile_pos_y);
		tiles[i] = tile;

		if (tile_pos_x == (pos_x + 960)) {
			tile_pos_x = pos_x;
			tile_pos_y += 64;
		}
		else {
			tile_pos_x += 64;
		}
	}
}

void Level::delete_level()
{
	for (auto it = tiles.begin(); it != tiles.end(); it++) {
		it->second.destroy_collider();
	}
}

void Level::spawn_enemies()
{
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		Tile* tile = create_spawn_point();
		it->second.set_pos(tile->get_pos_x(), tile->get_pos_y());
		if (it->second.is_active() == false)
			it->second.set_active(true);
	}
}

Tile* Level::create_spawn_point()
{
	int rand = std::rand() % 176 + 1;
	if (tiles[rand].get_type() != WALL) {
		return &tiles[rand];
	}

	return create_spawn_point();
}

void Level::despawn_enemies()
{
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		it->second.set_active(false);
	}
}

void Level::move_level(SwitchDirection dir)
{
	for (auto it = tiles.begin(); it != tiles.end(); it++) {
		if(dir == SWITCH_UP)
			it->second.move_rect(0, 8);
		if (dir == SWITCH_DOWN)
			it->second.move_rect(0, -8);
		if (dir == SWITCH_LEFT)
			it->second.move_rect(8, 0);
		if (dir == SWITCH_RIGHT)
			it->second.move_rect(-8, 0);

	}
}

void Level::render_level(SDL_Renderer* p_renderer)
{
	if (do_render_level) {
		for (auto it = tiles.begin(); it != tiles.end(); it++) {
			it->second.render(p_renderer);
		}

		for (auto it = enemies.begin(); it != enemies.end(); it++) {
			it->second.render(p_renderer);
		}

		if (level_type == LEVEL_CAVE) {	
			fire_1->render(p_renderer);
			fire_2->render(p_renderer);
			if (old_man != nullptr)
				old_man->render(p_renderer);
			if(sword != nullptr)
				sword->render(p_renderer);
			if(text != nullptr)
				SDL_RenderCopy(p_renderer, text->get_texture(), &text->get_area(), &text_rect);
		}
	}
}

void Level::update_level(Player* player)
{
	if (check_collision) {
		// TILE COLLISION
		std::map<int, Tile*> coll_tiles;
		int n = 0;

		for (auto it = tiles.begin(); it != tiles.end(); it++) {
			if (it->second.get_collider() != nullptr) {
				coll_tiles[n] = &it->second;
				n++;
			}
		}
		for (int i = 0; i < coll_tiles.size(); i++) {
			Collider* coll_b = coll_tiles[i]->get_collider();
			if (Service<CollisionManager>::Get()->check_collision(player->get_collider(), coll_b)) {
				player->on_collision(coll_tiles[i]);
			}
			for (auto it = enemies.begin(); it != enemies.end(); it++) {
				if (Service<CollisionManager>::Get()->check_collision(it->second.get_collider(), coll_b)) {
					it->second.on_collision(coll_tiles[i]);
				}
			}
		}

		// PLAYER / ENEMY COLLISION
		for (auto it = enemies.begin(); it != enemies.end(); it++) {
			if (Service<CollisionManager>::Get()->check_collision(it->second.get_collider(), player->get_collider())) {
				player->on_collision(&it->second);
				if (player->player_attacking())
					it->second.on_collision(player);
			}
		}

		// PLAYER / ACTIVATOR COLLISION
		if (level_type == LEVEL_CAVE) {
			if (sword != nullptr) {
				if (Service<CollisionManager>::Get()->check_collision(player->get_collider(), sword->get_collider())) {
					player->on_collision(sword);
					sword = nullptr;
					old_man = nullptr;
					text = nullptr;
				}
			}
		}
	}


	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		it->second.update(tiles);
		it->second.update();
	}

	for (auto it = enemies.begin(); it != enemies.cend(); ) {
		if (it->second.enemy_death())
			enemies.erase(it++);
		else
			++it;
	}
}

void Level::disable_hitboxes(bool disable)
{
	for (auto it = tiles.begin(); it != tiles.end(); it++) {
		it->second.disable_hitbox(disable);
	}
}
