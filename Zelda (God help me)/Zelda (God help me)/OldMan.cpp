#include "OldMan.h"
#include "Service.h"
#include "SpriteManager.h"

OldMan::OldMan(int p_x, int p_y)
{
	m_rect.x = p_x;
	m_rect.y = p_y;
	m_rect.w = 64;
	m_rect.h = 64;

	m_type = SCENERY;

	m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Cave/old_man.png", 0, 0, 64, 64);
}

void OldMan::render(SDL_Renderer * p_renderer)
{
	if (m_sprite != NULL)
		SDL_RenderCopy(p_renderer, m_sprite->get_texture(), &m_sprite->get_area(), &m_rect);
}

void OldMan::update()
{
}
