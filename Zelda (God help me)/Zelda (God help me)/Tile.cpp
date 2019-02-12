#include "Tile.h"
#include "Service.h"
#include "SpriteManager.h"

#include <iostream>

Tile::Tile(TileType p_type, int p_posX, int p_posY)
{
	m_tile_type = p_type;

	m_rect.x = p_posX; m_rect.y = p_posY;
	m_rect.w = 64; m_rect.h = 64;

	if (m_tile_type == FOREST || m_tile_type == FOREST_TOP || m_tile_type == FOREST_CORNER_1 || m_tile_type == FOREST_CORNER_2 || m_tile_type == FOREST_CORNER_3 || m_tile_type == FOREST_CORNER_4 || m_tile_type == TREE || m_tile_type == BUSH || m_tile_type == CAVE_WALL || m_tile_type == CAVE_WALL_TOP) {
		m_collider = new RectangleCollider(m_rect.x, m_rect.y, m_rect.w, m_rect.h);
		m_type = WALL;
	}
	else if (m_tile_type == CAVE) {
		m_collider = new RectangleCollider(m_rect.x, m_rect.y, m_rect.w, m_rect.h / 2);
		m_type = ACTIVATOR;
	}
	else {
		m_collider = nullptr;
		m_type = NO_WALL;
	}

	if (m_tile_type == GROUND)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/ground.png", 0, 0, 64, 64);
	if (m_tile_type == FOREST)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/forest.png", 0, 0, 64, 64);
	if (m_tile_type == FOREST_TOP)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/forest_top.png", 0, 0, 64, 64);
	if (m_tile_type == FOREST_CORNER_1)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/forest_corner_1.png", 0, 0, 64, 64);
	if (m_tile_type == FOREST_CORNER_2)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/forest_corner_2.png", 0, 0, 64, 64);
	if (m_tile_type == FOREST_CORNER_3)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/forest_corner_3.png", 0, 0, 64, 64);
	if (m_tile_type == FOREST_CORNER_4)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/forest_corner_4.png", 0, 0, 64, 64);
	if (m_tile_type == TREE)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/tree.png", 0, 0, 64, 64);
	if (m_tile_type == BUSH)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/bush.png", 0, 0, 64, 64);
	if (m_tile_type == CAVE)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/cave.png", 0, 0, 64, 64);
	if (m_tile_type == CAVE_GROUND)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Terrain/cave.png", 0, 0, 64, 64);
	if (m_tile_type == CAVE_WALL)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Cave/cave_wall.png", 0, 0, 64, 64);
	if (m_tile_type == CAVE_WALL_TOP)
		m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Cave/cave_wall_top.png", 0, 0, 64, 64);
}

void Tile::render(SDL_Renderer* p_renderer)
{
	if (m_sprite != nullptr) {
		SDL_RenderCopy(p_renderer, m_sprite->get_texture(), &m_sprite->get_area(), &m_rect);
		SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 1);
	}
	
	// Show Collider
	//if (m_collider != nullptr)
	//	SDL_RenderDrawRect(p_renderer, &m_collider->get_bounds());

}

void Tile::move_rect(int x, int y)
{
	if (x < 0 && y == 0) {
		m_rect.x += x;
	}
	if (x > 0 && y == 0) {
		m_rect.x += x;
	}
	if (y < 0 && x == 0) {
		m_rect.y += y;
	}
	if (y > 0 && x == 0) {
		m_rect.y += y;
	}

	if(m_collider != nullptr)
		m_collider->set_position(m_rect.x, m_rect.y);
}

void Tile::disable_hitbox(bool disable)
{
	if (disable) {
		if (m_collider != nullptr)
			m_collider = nullptr;
	}
	else if (!disable) {
		if(m_collider == nullptr)
			if(m_type == WALL)
				m_collider = new RectangleCollider(m_rect.x, m_rect.y, m_rect.w, m_rect.h);
			if(m_type == ACTIVATOR)
				m_collider = new RectangleCollider(m_rect.x, m_rect.y, m_rect.w, m_rect.h / 2);
	}
}

bool Tile::has_pos(int x, int y)
{
	if (m_rect.x == x && m_rect.y == y)
		return true;
	else
		return false;
}

void Tile::destroy_collider()
{
	delete m_collider;
	m_collider = nullptr;
}
