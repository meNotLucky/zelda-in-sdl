#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"

enum TileType {
	GROUND,
	FOREST,
	FOREST_TOP,
	FOREST_CORNER_1,
	FOREST_CORNER_2,
	FOREST_CORNER_3,
	FOREST_CORNER_4,
	TREE,
	BUSH,
	CAVE,
	CAVE_GROUND,
	CAVE_WALL,
	CAVE_WALL_TOP
};

class Tile : public GameObject {

	TileType m_tile_type;

public:
	Tile() {};
	Tile(TileType p_type, int p_posX, int p_posY);
	void update() {};
	void render(SDL_Renderer* p_renderer);
	void move_rect(int x, int y);
	void disable_hitbox(bool disable);
	Collider* get_collider() { return m_collider; };
	bool has_pos(int x, int y);
};