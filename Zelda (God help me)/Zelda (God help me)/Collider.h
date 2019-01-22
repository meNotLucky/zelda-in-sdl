#pragma once

#include <SDL.h>

enum COLLIDERTYPE {

	RECTANGLE,
	TRIANGLE,
	CIRCLE,
	POLYGON,
	COLLIDER_COUNT
};

class Collider {

protected:
	SDL_Rect m_bounds;
	COLLIDERTYPE m_type;

public:
	Collider() {};
	virtual ~Collider() {};
	virtual SDL_Rect get_bounds() = 0;
	COLLIDERTYPE get_type() { return m_type; }
	void set_position(int p_x, int p_y);
};

class RectangleCollider : public Collider {


public:
	RectangleCollider(int p_x, int p_y, int p_w, int p_h);
	~RectangleCollider();
	SDL_Rect get_bounds();

};