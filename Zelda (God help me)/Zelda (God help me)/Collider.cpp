#include "Collider.h"

RectangleCollider::RectangleCollider(int p_x, int p_y, int p_w, int p_h)
{
	m_type = COLLIDERTYPE::RECTANGLE;

	m_bounds.x = p_x;
	m_bounds.y = p_y;
	m_bounds.w = p_w;
	m_bounds.h = p_h;
}

RectangleCollider::~RectangleCollider()
{
}

SDL_Rect RectangleCollider::get_bounds()
{
	return m_bounds;
}

void Collider::set_position(int p_x, int p_y)
{
	m_bounds.x = p_x;
	m_bounds.y = p_y;
}
