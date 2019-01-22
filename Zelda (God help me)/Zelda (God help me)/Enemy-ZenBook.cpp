#include "Enemy.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Collider.h"
#include <iostream>

Enemy::Enemy(int spawn_x, int spawn_y)
{
	m_active = false;

	timer = 0;
	rand = 0;

	m_x = spawn_x;
	m_y = spawn_y;

	speed_x = 5;
	speed_y = 5;

	m_rect.x = m_x;
	m_rect.y = m_y;
	m_rect.w = 64;
	m_rect.h = 64;

	m_collider = new RectangleCollider(m_rect.x, m_rect.y, m_rect.w, m_rect.h);

	anim_up = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/walking_enemy_up.png", 0, 0, 64, 64);
	anim_down = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/walking_enemy_down.png", 0, 0, 64, 64);
	anim_left = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/walking_enemy_left.png", 0, 0, 64, 64);
	anim_right = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/walking_enemy_right.png", 0, 0, 64, 64);
}

void Enemy::render(SDL_Renderer * p_renderer)
{
	if (m_active == true) {

		if (dir == MOVE_UP)
			anim_up->render_animation(p_renderer, 32, true, &m_rect);
		if (dir == MOVE_DOWN)
			anim_down->render_animation(p_renderer, 32, true, &m_rect);
		if (dir == MOVE_LEFT)
			anim_left->render_animation(p_renderer, 32, true, &m_rect);
		if (dir == MOVE_RIGHT)
			anim_right->render_animation(p_renderer, 32, true, &m_rect);
	}

	// Show Collider
	//SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 1);
	//SDL_RenderDrawRect(p_renderer, &m_collider->get_bounds());
}

void Enemy::update()
{
	if (m_active == true) {

		if (timer > 2.0f) {
			rand = std::rand() % 4 + 1;
			timer = 0;
		}

		if (rand < 1) {
			m_rect.x += 2;
			dir = MOVE_RIGHT;
		}
		if (rand >= 1 && rand < 2) {
			m_rect.x -= 2;
			dir = MOVE_LEFT;
		}
		if (rand >= 2 && rand < 3) {
			m_rect.y += 2;
			dir = MOVE_DOWN;
		}
		if (rand >= 3 && rand <= 4) {
			m_rect.y -= 2;
			dir = MOVE_UP;
		}

		timer += 1.0f / 60;
	}

	m_collider->set_position(m_rect.x, m_rect.y);
}

void Enemy::on_collision(GameObject * p_other)
{
	if (p_other->get_type() == WALL) {

		int other_x = p_other->get_collider()->get_bounds().x;
		int other_y = p_other->get_collider()->get_bounds().y;
		int other_w = p_other->get_collider()->get_bounds().w;
		int other_h = p_other->get_collider()->get_bounds().h;

		if (m_rect.x + m_rect.w >= other_x) {
			if (m_rect.y + m_rect.h > other_y + 10 && m_rect.y + m_rect.h / 2 < other_y + other_h - 10) {

				if (m_rect.x + m_rect.w - other_x > m_rect.w) {
					m_rect.x = other_x + other_w;
					std::cout << "Hit" << std::endl;
				}

				if (m_rect.x + m_rect.w - other_x < m_rect.w) {
					m_rect.x = other_x - other_w;
					//std::cout << "Hit" << std::endl;
				}
			}
		}

		if (m_rect.y + m_rect.h >= other_y) {
			if (m_rect.x + m_rect.w > other_x + 10 && m_rect.x < other_x + other_w - 10) {

				if (m_rect.y + m_rect.h - other_y > m_rect.h / 2) {
					m_rect.y = other_y + other_h - m_rect.h / 2;
					//std::cout << "Hit" << std::endl;
				}

				if (m_rect.y + m_rect.h - other_y < m_rect.h / 2) {
					m_rect.y = other_y - other_h;
					//std::cout << "Hit" << std::endl;
				}
			}
		}
	}
}
