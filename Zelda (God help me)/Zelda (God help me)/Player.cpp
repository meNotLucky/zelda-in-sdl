#include "Player.h"
#include "Service.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "WorldManager.h"
#include "Collider.h"

#include <iostream>

Player::Player()
{
	speed_x = 5;
	speed_y = 5;

	m_rect.x = 500; m_rect.y = 580;
	m_rect.w = 64; m_rect.h = 64;

	m_health = 6;

	aquired_sword = false;
	can_attack = false;
	is_attacking = false;
	can_move = true;
	is_dead = false;
	death_sound_played = false;

	m_type = PLAYER;
	m_collider = new RectangleCollider(m_rect.x, m_rect.y + m_rect.h / 2, m_rect.w, m_rect.h / 2);

	m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_up.png", 0, 0, 60, 64);
	anim_up = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/walking_up.png", 0, 0, 60, 64);
	anim_down = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/walking_down.png", 0, 0, 60, 64);
	anim_left = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/walking_left.png", 0, 0, 60, 64);
	anim_right = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/walking_right.png", 0, 0, 60, 64);
	anim_going_up = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/going_up.png", 0, 0, 60, 64);
	anim_going_down = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/going_down.png", 0, 0, 60, 64);
	anim_aquire_sword = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/aquire_sword.png", 0, 0, 64, 128);
	anim_atk_up = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/atk_up.png", 0, 0, 64, 112);
	anim_atk_down = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/atk_down.png", 0, 0, 64, 108);
	anim_atk_left = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/atk_left.png", 0, 0, 108, 64);
	anim_atk_right = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/atk_right.png", 0, 0, 108, 64);
	anim_death = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Link/anim_death.png", 0, 0, 60, 64);

	sound_sword_slash = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/sword_slash.wav");
	//sound_sword_shoot = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/sword_shoot.wav");
	//sound_shield = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/sheild.wav");
	sound_hurt = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/hurt.wav");
	sound_die = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/death.wav");
	//sound_get_heart = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/get_heart.wav");
	//sound_low_health = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/low_health.wav");
	//sound_get_rupee = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/get_rupee.wav");
	sound_stairs = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/stairs.wav");
	sound_aquire_sword = Service<AudioManager>::Get()->create_sound("Assets/Audio/Link/aquire_sword.wav");

}

void Player::render(SDL_Renderer * p_renderer)
{
	if (is_moving) {
		if (last_dir == UP)
			anim_up->render_animation(p_renderer, 8, true, &m_rect);
		if (last_dir == DOWN)
			anim_down->render_animation(p_renderer, 8, true, &m_rect);
		if (last_dir == LEFT)
			anim_left->render_animation(p_renderer, 8, true, &m_rect);
		if (last_dir == RIGHT)
			anim_right->render_animation(p_renderer, 8, true, &m_rect);
	}
	else {
		if(m_sprite != nullptr)
			SDL_RenderCopy(p_renderer, m_sprite->get_texture(), &m_sprite->get_area(), &m_rect);
	}

	if (going_up) {
		if (anim_going_up->render_animation(p_renderer, 16, false, &m_rect)) {
			set_pos(256, 320);
			can_move = false;
			m_sprite = nullptr;
		}
		else {
			can_move = true;
			m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_down.png", 0, 0, 60, 64);
			going_up = false;
		}
	}
	if (going_down) {
		if (anim_going_down->render_animation(p_renderer, 16, false, &m_rect)) {
			Service<AudioManager>::Get()->stop_music();
			can_move = false;
			m_sprite = nullptr;
		}
		else {
			Service<WorldManager>::Get()->enter_cave_level(this);
			set_pos(448, 836);
			can_move = true;
			m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_up.png", 0, 0, 60, 64);
			going_down = false;
		}
	}

	if (aquired_sword) {
		m_rect.y -= 16;
		m_rect.h = 128;
		if (anim_aquire_sword->render_animation(p_renderer, 16, false, &m_rect)) {
			m_sprite = nullptr;
			can_move = false;
		}
		else {
			m_rect.y += 64;
			m_rect.h = 64;
			can_move = true;
			m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_down.png", 0, 0, 60, 64);
			can_attack = true;
			aquired_sword = false;
		}
	}

	if (is_attacking) {
		m_sprite = nullptr;
		if (last_dir == UP) {
			m_rect.h = 112;
			if (anim_atk_up->render_animation(p_renderer, 4, false, &m_rect)) {
				can_move = false;
			}
			else {
				m_rect.h = 64;
				m_rect.y += 48;
				m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_up.png", 0, 0, 60, 64);
				is_attacking = false;
				can_attack = true;
				can_move = true;
			}
		}
		if (last_dir == DOWN) {
			m_rect.h = 108;
			if (anim_atk_down->render_animation(p_renderer, 4, false, &m_rect)) {
				can_move = false;
			}
			else {
				m_rect.h = 64;
				m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_down.png", 0, 0, 60, 64);
				is_attacking = false;
				can_attack = true;
				can_move = true;
			}
		}
		if (last_dir == LEFT) {
			m_rect.w = 108;
			if (anim_atk_left->render_animation(p_renderer, 4, false, &m_rect)) {
				can_move = false;
			}
			else {
				m_rect.w = 64;
				m_rect.x += 44;
				m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_left.png", 0, 0, 60, 64);
				is_attacking = false;
				can_attack = true;
				can_move = true;
			}
		}
		if (last_dir == RIGHT) {
			m_rect.w = 108;
			if (anim_atk_right->render_animation(p_renderer, 4, false, &m_rect)) {
				can_move = false;
			}
			else {
				m_rect.w = 64;
				m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_right.png", 0, 0, 60, 64);
				is_attacking = false;
				can_attack = true;
				can_move = true;
			}
		}
	}

	if (m_health <= 0) {
		can_move = false;
		is_dead = true;
		m_sprite = nullptr;
		Service<AudioManager>::Get()->stop_music();
		if (!death_sound_played) {
			sound_die->play_sound(0);
			death_sound_played = true;
		}
		if (!anim_death->render_animation(p_renderer, 32, false, &m_rect)) {
			anim_finished = true;
		}
	}

	// Show Collider
	//SDL_SetRenderDrawColor(p_renderer, 255, 0, 0, 1);
	//SDL_RenderDrawRect(p_renderer, &m_collider->get_bounds());
}

void Player::update()
{
	is_moving = false;

	if (can_move) {

		if (Service<InputManager>::Get()->key_down(SDL_SCANCODE_DOWN)) {
			last_dir = DOWN;
			m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_down.png", 0, 0, 60, 64);
			m_rect.y += speed_y;
			m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
			is_moving = true;
		}
		else if (Service<InputManager>::Get()->key_down(SDL_SCANCODE_UP)) {
			last_dir = UP;
			m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_up.png", 0, 0, 60, 64);
			m_rect.y -= speed_y;
			m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
			is_moving = true;
		}
		else if (Service<InputManager>::Get()->key_down(SDL_SCANCODE_RIGHT))
		{
			last_dir = RIGHT;
			m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_right.png", 0, 0, 60, 64);
			m_rect.x += speed_x;
			m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
			is_moving = true;
		}
		else if (Service<InputManager>::Get()->key_down(SDL_SCANCODE_LEFT)) {
			last_dir = LEFT;
			m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_left.png", 0, 0, 60, 64);
			m_rect.x -= speed_x;
			m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
			is_moving = true;
		}
	}

	if (can_attack) {
		if (Service<InputManager>::Get()->key_pressed(SDL_SCANCODE_X)) {
			if(last_dir == UP)
				m_rect.y -= 48;
			if(last_dir == LEFT)
				m_rect.x -= 44;
			is_attacking = true;
			can_attack = false;
			sound_sword_slash->play_sound(0);
		}
	}

	if (is_immune) {
		timer += 1 / 60.0f;
		if (timer > 0.4) {
			is_immune = false;
			timer = 0;
		}
	}

	m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
}

void Player::move_rect(int x, int y)
{

	if (x < 0 && y == 0) {
		m_rect.x += x;
		m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
	}
	if (x > 0 && y == 0) {
		m_rect.x += x;
		m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
	}
	if (y < 0 && x == 0) {
		m_rect.y += y;
		m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
	}
	if (y > 0 && x == 0) {
		m_rect.y += y;
		m_collider->set_position(m_rect.x, m_rect.y + m_rect.h / 2);
	}

}

void Player::on_collision(GameObject * p_other)
{

	int other_x = p_other->get_collider()->get_bounds().x;
	int other_y = p_other->get_collider()->get_bounds().y;
	int other_w = p_other->get_collider()->get_bounds().w;
	int other_h = p_other->get_collider()->get_bounds().h;

	if (p_other->get_type() == SWORD) {
		sound_aquire_sword->play_sound(0);
		aquired_sword = true;
	}

	if (p_other->get_type() == WALL) {

		if (m_rect.x + m_rect.w >= other_x) {
			if (m_rect.y + m_rect.h > other_y + 10 && m_rect.y + m_rect.h / 2 < other_y + other_h - 10) {

				if (m_rect.x + m_rect.w - other_x > m_rect.w)
					m_rect.x = other_x + other_w;

				if (m_rect.x + m_rect.w - other_x < m_rect.w)
					m_rect.x = other_x - other_w;
			}
		}

		if (m_rect.y + m_rect.h >= other_y) {
			if (m_rect.x + m_rect.w > other_x + 10 && m_rect.x < other_x +  other_w - 10) {

				if (m_rect.y + m_rect.h - other_y > m_rect.h / 2)
					m_rect.y = other_y + other_h - m_rect.h / 2;

				if (m_rect.y + m_rect.h - other_y < m_rect.h / 2)
					m_rect.y = other_y - other_h;
			}
		}
	}
	if (p_other->get_type() == ACTIVATOR) {

		if (m_rect.x + m_rect.w >= other_x) {
			if (m_rect.y + m_rect.h > other_y + 10 && m_rect.y + m_rect.h / 2 < other_y + other_h - 10) {

				if (m_rect.x + m_rect.w - other_x > m_rect.w)
					m_rect.x = other_x + other_w;

				if (m_rect.x + m_rect.w - other_x < m_rect.w)
					m_rect.x = other_x - other_w;
			}
		}

		if (m_rect.y + m_rect.h >= other_y) {
			if (m_rect.x + m_rect.w > other_x + 10 && m_rect.x < other_x + other_w - 10) {

				if (m_rect.y + m_rect.h - other_y > m_rect.h / 2)
					m_rect.y = other_y + other_h - m_rect.h / 2;

				if (m_rect.y + m_rect.h - other_y < m_rect.h / 2)
					m_rect.y = other_y - other_h;
			}
		}
		sound_stairs->play_sound(0);
		going_down = true;
	}

	if (p_other->get_type() == ENEMY) {
		if (!is_attacking) {
			if (!is_immune) {
				is_immune = true;
				m_health--;
				sound_hurt->play_sound(0);
				if (last_dir == UP) {
					m_rect.y += 130;
				}
				if (last_dir == DOWN) {
					m_rect.y -= 130;
				}
				if (last_dir == LEFT) {
					m_rect.x += 130;
				}
				if (last_dir == RIGHT) {
					m_rect.x -= 130;
				}
			}
		}
	}
}

bool Player::player_death()
{
	if (is_dead)
		return true;
	else
		return false;
}

void Player::reset_player()
{
	m_rect.x = 500; m_rect.y = 580;
	m_rect.w = 64; m_rect.h = 64;

	m_health = 6;

	m_sprite = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Link/idle_up.png", 0, 0, 60, 64);

	aquired_sword = false;
	can_attack = false;
	is_attacking = false;
	can_move = true;
	is_dead = false;
}
