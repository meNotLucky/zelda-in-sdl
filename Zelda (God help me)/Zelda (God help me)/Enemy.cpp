#include "Enemy.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Collider.h"
#include <iostream>

Enemy::Enemy(int spawn_x, int spawn_y, EnemyType e_type)
{
	m_active = false;
	can_move = false;
	can_attack = true;
	has_spawned = false;

	m_type = ENEMY;
	enemy_type = e_type;

	m_rect.x = spawn_x;
	m_rect.y = spawn_y;
	m_rect.w = 64;
	m_rect.h = 64;

	timer_1 = 0;
	rand = 0;
	new_move = 0;
	//prev_move = 0;
	//new_x = m_rect.x;
	//new_y = m_rect.y;
	//start_y = m_rect.y;
	//hit_height = false;

	projectile = nullptr;
	proj_cooldown = 0;

	m_collider = new RectangleCollider(m_rect.x, m_rect.y, m_rect.w, m_rect.h);
	m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Enemies/spawn_still.png", 0, 0, 64, 64);
	spawning = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/spawn.png", 0, 0, 64, 64);

	if (enemy_type == WALKING) {
		anim_up = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/walking_enemy_up.png", 0, 0, 64, 64);
		anim_down = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/walking_enemy_down.png", 0, 0, 64, 64);
		anim_left = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/walking_enemy_left.png", 0, 0, 64, 64);
		anim_right = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/walking_enemy_right.png", 0, 0, 64, 64);
		speed_x = 2;
		speed_y = 2;
	}
	else if (enemy_type == JUMPING) {
		jumping = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Enemies/jumping_enemy.png", 0, 0, 64, 64);
		speed_x = 7;
		speed_y = 7;
	}
}

void Enemy::render(SDL_Renderer * p_renderer)
{
	if (m_active == true) {
		if (!has_spawned) {
			if (spawning->render_animation(p_renderer, 16, false, &m_rect)) {
				can_move = false;
			}
			else {
				has_spawned = true;
				can_move = true;
			}
		}
		else {
			if (enemy_type == WALKING) {
				if (dir == MOVE_UP)
					anim_up->render_animation(p_renderer, 28, true, &m_rect);
				if (dir == MOVE_DOWN)
					anim_down->render_animation(p_renderer, 28, true, &m_rect);
				if (dir == MOVE_LEFT)
					anim_left->render_animation(p_renderer, 28, true, &m_rect);
				if (dir == MOVE_RIGHT)
					anim_right->render_animation(p_renderer, 28, true, &m_rect);
			}
			else if (enemy_type == JUMPING) {
				jumping->render_animation(p_renderer, 16, true, &m_rect);
			}
		}

		if (projectile != nullptr)
			projectile->render(p_renderer);
	}
	else {
		timer_1 = 0;
	}

	// Show Collider
	//SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 1);
	//SDL_RenderDrawRect(p_renderer, &m_collider->get_bounds());
}

bool Enemy::get_new_move(MovingDirection move_dir_1, MovingDirection move_dir_2)
{
	if (enemy_type == WALKING) {
		if(move_dir_1 == MOVE_LEFT && move_dir_2 == MOVE_RIGHT)
			new_move = std::rand() % 2 + 1;
		if (move_dir_1 == MOVE_UP && move_dir_2 == MOVE_DOWN)
			new_move = std::rand() % 4 + 3;
	}
	//if (enemy_type == JUMPING) {
	//	new_move = std::rand() % 4 + 1;

	//	if (new_move == 1) {
	//		new_x = m_rect.x - 100;
	//		new_y = m_rect.y - 100;
	//	}
	//	if (new_move == 2) {
	//		new_x = m_rect.x + 100;
	//		new_y = m_rect.y - 100;
	//	}
	//	if (new_move == 3) {
	//		new_x = m_rect.x - 100;
	//		new_y = m_rect.y + 100;
	//	}
	//	if (new_move == 4) {
	//		new_x = m_rect.x + 100;
	//		new_y = m_rect.y + 100;
	//	}

	//	if (new_x < 64)
	//		return false;
	//	if (new_x > 960)
	//		return false;
	//	if (new_y < 320)
	//		return false;
	//	if (new_x > 896)
	//		return false;

	//}

	return true;
}

void Enemy::fire_projectile(MovingDirection dir)
{
	if (dir == MOVE_UP)
		projectile = new EnemyProjectile((m_rect.x + m_rect.w / 2) - 15, m_rect.y, FIRE_UP);
	if (dir == MOVE_DOWN)
		projectile = new EnemyProjectile(m_rect.x + m_rect.w / 2 - 15, m_rect.y + m_rect.h, FIRE_DOWN);
	if (dir == MOVE_LEFT)
		projectile = new EnemyProjectile(m_rect.x, m_rect.y + m_rect.h / 2 - 16, FIRE_LEFT);
	if (dir == MOVE_RIGHT)
		projectile = new EnemyProjectile(m_rect.x + m_rect.w, m_rect.y + m_rect.h / 2 - 16, FIRE_RIGHT);
}

void Enemy::update(std::map<int, Tile> p_tiles)
{

	if (enemy_type == WALKING) {

		if (can_move) {

			for (int i = 0; i < p_tiles.size(); i++) {
				if (p_tiles[i].has_pos(m_rect.x, m_rect.y)) {
					rand = std::rand() % 2 + 1;
					if(rand == 1)
					{
						new_move = std::rand() % 4 + 1;

						if (projectile == nullptr) {
							if (proj_cooldown <= 0) {
								if (new_move == 1)
									fire_projectile(MOVE_RIGHT);
								if (new_move == 2)
									fire_projectile(MOVE_LEFT);
								if (new_move == 3)
									fire_projectile(MOVE_DOWN);
								if (new_move == 4)
									fire_projectile(MOVE_UP);
								proj_cooldown = 4;
							}
						}
					}
				}
			}

			if (new_move == 1) {
				dir = MOVE_RIGHT;
				m_rect.x += speed_x;
			}
			if (new_move == 2) {
				dir = MOVE_LEFT;
				m_rect.x -= speed_x;
			}
			if (new_move == 3) {
				dir = MOVE_DOWN;
				m_rect.y += speed_y;
			}
			if (new_move == 4) {
				dir = MOVE_UP;
				m_rect.y -= speed_y;
			}

			if (m_rect.x < 0) {
				m_rect.x = 0;
				get_new_move(MOVE_UP, MOVE_DOWN);
			}
			if (m_rect.x > 960) {
				m_rect.x = 960;
				get_new_move(MOVE_UP, MOVE_DOWN);
			}
			if (m_rect.y < 256) {
				m_rect.y = 256;
				get_new_move(MOVE_LEFT, MOVE_RIGHT);
			}
			if (m_rect.y > 896) {
				m_rect.x = 896;
				get_new_move(MOVE_LEFT, MOVE_RIGHT);
			}

		}
	}

}

void Enemy::update()
{

	if (projectile != nullptr) {
		projectile->update();
	}

	if (proj_cooldown > 0)
		proj_cooldown -= 1.0f / 60;
	else
		proj_cooldown = 0;

	if (projectile != nullptr) {
		if (projectile->get_pos_x() < 0 || projectile->get_pos_x() > 1024 - projectile->get_collider()->get_bounds().w || projectile->get_pos_y() < 256 || projectile->get_pos_y() > 960 - projectile->get_collider()->get_bounds().h) {
			delete projectile;
			projectile = nullptr;
		}
	}

	if (m_active == true) {

		//if (enemy_type == JUMPING) {

		//	if (can_move) {

		//		if (m_rect.x < 0) {
		//			m_rect.x = 0;
		//			get_new_move(MOVE_UP, MOVE_DOWN);
		//		}
		//		if (m_rect.x + m_rect.w > 1024) {
		//			m_rect.x = 1024 - m_rect.w;
		//			get_new_move(MOVE_UP, MOVE_DOWN);
		//		}
		//		if (m_rect.y < 256) {
		//			m_rect.y = 256;
		//			get_new_move(MOVE_LEFT, MOVE_RIGHT);
		//		}
		//		if (m_rect.y + m_rect.h > 960) {
		//			m_rect.y = 960 - m_rect.h;
		//			get_new_move(MOVE_LEFT, MOVE_RIGHT);
		//		}

		//		rand = std::rand() % 3 + 1;

		//		if (timer_2 > rand) {

		//			//while (!get_new_move()) {
		//			//	get_new_move();
		//			//}

		//			std::cout << new_x << std::endl;
		//			std::cout << new_y << std::endl;

		//			timer_2 = 0;
		//		}

		//		if (start_y < new_y) {
		//			int jump_height = start_y - 64;

		//			if (!hit_height) {
		//				if (m_rect.y > jump_height) {
		//					m_rect.y -= speed_y;
		//					if (m_rect.y <= jump_height)
		//						hit_height = true;
		//				}
		//			}
		//			if (hit_height) {
		//				if (m_rect.y < new_y) {
		//					m_rect.y += speed_y;
		//				}
		//				else {
		//					m_rect.y = new_y;
		//					start_y = m_rect.y;
		//					speed_y = 5;
		//					hit_height = false;
		//				}
		//			}
		//		}

		//		if (start_y > new_y) {
		//			int jump_height = new_y - 64;

		//			if (!hit_height) {
		//				if (m_rect.y > jump_height) {
		//					m_rect.y -= speed_y;
		//					if (m_rect.y <= jump_height)
		//						hit_height = true;
		//				}
		//			}
		//			if (hit_height) {
		//				if (m_rect.y < new_y) {
		//					m_rect.y += speed_y;
		//				}
		//				else {
		//					m_rect.y = new_y;
		//					start_y = m_rect.y;
		//					speed_y = 5;
		//					hit_height = false;
		//				}
		//			}
		//		}

		//		if (m_rect.x < new_x) {
		//			if (m_rect.x != new_x)
		//				m_rect.x += speed_x;
		//		}

		//		if (m_rect.x > new_x) {
		//			if (m_rect.x != new_x)
		//				m_rect.x -= speed_x;
		//		}

		//		timer_2 += 1.0f / 60;
		//	}

		//}

		m_collider->set_position(m_rect.x, m_rect.y);
	}
	else {
		has_spawned = false;
	}

}



void Enemy::on_collision(GameObject * p_other)
{
	if (m_active == true) {

		// WALL COLLISIONS
		if (p_other->get_type() == WALL) {
			if (enemy_type == WALKING) {
				int other_x = p_other->get_collider()->get_bounds().x;
				int other_y = p_other->get_collider()->get_bounds().y;
				int other_w = p_other->get_collider()->get_bounds().w;
				int other_h = p_other->get_collider()->get_bounds().h;

				if (m_rect.x + m_rect.w >= other_x) {
					if (m_rect.y + m_rect.h > other_y + 10 && m_rect.y + m_rect.h / 2 < other_y + other_h - 10) {

						if (m_rect.x + m_rect.w - other_x > m_rect.w) {
							m_rect.x = other_x + other_w;
						}

						if (m_rect.x + m_rect.w - other_x < m_rect.w) {
							m_rect.x = other_x - other_w;
						}

						get_new_move(MOVE_UP, MOVE_DOWN);

					}
				}

				if (m_rect.y + m_rect.h >= other_y) {
					if (m_rect.x + m_rect.w > other_x + 10 && m_rect.x < other_x + other_w - 10) {

						if (m_rect.y + m_rect.h - other_y > m_rect.h) {
							m_rect.y = other_y + other_h;
						}

						if (m_rect.y + m_rect.h - other_y < m_rect.h) {
							m_rect.y = other_y - other_h;
						}

						get_new_move(MOVE_RIGHT, MOVE_LEFT);

					}
				}
			}
		}

		if (p_other->get_type() == PLAYER) {
			is_dead = true;
			m_active = false;
			delete m_collider;
			m_collider = nullptr;
		}
	}
}

bool Enemy::enemy_death()
{
	return is_dead;
}
