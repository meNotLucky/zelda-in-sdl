#pragma once

#include "Sprite.h"

struct Collider;
struct SDL_Renderer;

enum ObjectType {
	PLAYER,
	ENEMY,
	SCENERY,
	WALL,
	NO_WALL,
	SWORD,
	PROJECTILE,
	ACTIVATOR
};

class GameObject {
protected:

	// Object type
	ObjectType m_type;

	// Object rect
	SDL_Rect m_rect;

	// Object scale
	float m_scale;

	// Object active and movement
	bool m_active;

	// Object sprite
	Sprite* m_sprite;
	Collider* m_collider;

public:
	virtual ~GameObject() {};
	virtual void render(SDL_Renderer* p_renderer) {};
	virtual void update() = 0;
	virtual void on_collision(GameObject* p_other) {};

	// Getters
	int get_pos_x() { return m_rect.x; };
	int get_pos_y() { return m_rect.y; };
	void set_pos(int p_x, int p_y) { m_rect.x = p_x; m_rect.y = p_y; };
	ObjectType get_type() { return m_type; };
	Collider* get_collider() { return m_collider; };
};