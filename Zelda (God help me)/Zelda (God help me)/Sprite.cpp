#include "Sprite.h"

Sprite::Sprite(SDL_Texture * p_texture, int p_x, int p_y, int p_w, int p_h)
{
	m_texture = p_texture;
	m_area.x = p_x;
	m_area.y = p_y;
	m_area.w = p_w;
	m_area.h = p_h;
}

SDL_Texture * Sprite::get_texture()
{
	return m_texture;
}

SDL_Rect Sprite::get_area()
{
	return m_area;
}
