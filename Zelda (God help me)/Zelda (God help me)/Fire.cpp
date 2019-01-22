#include "Fire.h"
#include "Service.h"
#include "SpriteManager.h"

Fire::Fire(int p_x, int p_y)
{
	m_rect.x = p_x;
	m_rect.y = p_y;
	m_rect.w = 64;
	m_rect.h = 64;

	m_type = SCENERY;

	m_anim = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Cave/fire.png", 0, 0, 64, 64);
}

void Fire::render(SDL_Renderer * p_renderer)
{
	if (m_anim != nullptr)
		m_anim->render_animation(p_renderer, 8, true, &m_rect);
}

void Fire::update()
{
}
