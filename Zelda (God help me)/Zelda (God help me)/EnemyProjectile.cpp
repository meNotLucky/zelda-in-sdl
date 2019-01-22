#include "EnemyProjectile.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Collider.h"

EnemyProjectile::EnemyProjectile(int p_x, int p_y, FireDirection p_dir)
{
	m_type = PROJECTILE;
	m_rect.x = p_x;
	m_rect.y = p_y;
	m_rect.h = 32;
	m_rect.w = 30;

	fire_dir = p_dir;
	m_speed = 12;

	m_collider = new RectangleCollider(m_rect.x, m_rect.y, m_rect.w, m_rect.h);

	m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Items/enemy_projectile.png", 0, 0, 30, 32);
}

void EnemyProjectile::render(SDL_Renderer * p_renderer)
{
	if (m_sprite != nullptr)
		SDL_RenderCopy(p_renderer, m_sprite->get_texture(), &m_sprite->get_area(), &m_rect);
}

void EnemyProjectile::update()
{
	if (fire_dir == FIRE_UP)
		m_rect.y -= m_speed;
	if (fire_dir == FIRE_DOWN)
		m_rect.y += m_speed;
	if (fire_dir == FIRE_LEFT)
		m_rect.x -= m_speed;
	if (fire_dir == FIRE_RIGHT)
		m_rect.x += m_speed;
}
