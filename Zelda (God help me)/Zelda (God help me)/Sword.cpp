#include "Sword.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Collider.h"

Sword::Sword(int p_x, int p_y)
{
	m_type = SWORD;
	m_rect.x = p_x;
	m_rect.y = p_y;
	m_rect.h = 64;
	m_rect.w = 28;

	m_collider = new RectangleCollider(m_rect.x, m_rect.y, m_rect.w, m_rect.h);

	m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Items/sword_obj.png", 0, 0, 28, 64);
}

void Sword::render(SDL_Renderer * p_renderer)
{
	if (m_sprite != nullptr) {
		SDL_RenderCopy(p_renderer, m_sprite->get_texture(), &m_sprite->get_area(), &m_rect);
	}
}

void Sword::update()
{
}
