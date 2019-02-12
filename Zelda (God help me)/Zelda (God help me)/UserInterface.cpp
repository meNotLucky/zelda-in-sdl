#include "UserInterface.h"
#include "Service.h"
#include "SpriteManager.h"

UsierInterface::UsierInterface()
{
	m_rect.x = 0; m_rect.y = 0;
	m_rect.w = 1024; m_rect.h = 256;
	m_layout = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/UI/layout.png", 0, 0, 1024, 256);

	hearts_1_rect.x = 702; hearts_1_rect.y = 171; hearts_1_rect.w = 15; hearts_1_rect.h = 33;
	hearts_2_rect.x = 717; hearts_2_rect.y = 171; hearts_2_rect.w = 15; hearts_2_rect.h = 33;
	hearts_3_rect.x = 734; hearts_3_rect.y = 171; hearts_3_rect.w = 15; hearts_3_rect.h = 33;
	hearts_4_rect.x = 749; hearts_4_rect.y = 171; hearts_4_rect.w = 15; hearts_4_rect.h = 33;
	hearts_5_rect.x = 766; hearts_5_rect.y = 171; hearts_5_rect.w = 15; hearts_5_rect.h = 33;
	hearts_6_rect.x = 781; hearts_6_rect.y = 171; hearts_6_rect.w = 15; hearts_6_rect.h = 33;

	m_rects.push_back(hearts_1_rect);
	m_rects.push_back(hearts_2_rect);
	m_rects.push_back(hearts_3_rect);
	m_rects.push_back(hearts_4_rect);
	m_rects.push_back(hearts_5_rect);
	m_rects.push_back(hearts_6_rect);

	m_hearts.push_back(Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/UI/heart_1.png", 0, 0, 15, 33));
	m_hearts.push_back(Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/UI/heart_2.png", 0, 0, 15, 33));
	m_hearts.push_back(Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/UI/heart_1.png", 0, 0, 15, 33));
	m_hearts.push_back(Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/UI/heart_2.png", 0, 0, 15, 33));
	m_hearts.push_back(Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/UI/heart_1.png", 0, 0, 15, 33));
	m_hearts.push_back(Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/UI/heart_2.png", 0, 0, 15, 33));

	current_health = 6;
}

UsierInterface::~UsierInterface()
{
	delete m_sword;
	m_sword = nullptr;
}

void UsierInterface::render(SDL_Renderer * p_renderer)
{
	if (m_layout != nullptr)
		SDL_RenderCopy(p_renderer, m_layout->get_texture(), &m_layout->get_area(), &m_rect);
	if (m_sword != nullptr)
		m_sword->render(p_renderer);

	for (int i = 0; i < m_hearts.size(); i++) {
		if (m_hearts[i] != nullptr)
			SDL_RenderCopy(p_renderer, m_hearts[i]->get_texture(), &m_hearts[i]->get_area(), &m_rects[i]);
	}
}

void UsierInterface::update(Player * player)
{
	if (player->get_sword()) {
		m_sword = new Sword(610, 110);
	}

	if (current_health != player->get_health()) {
		if(!m_hearts.empty())
			m_hearts.pop_back();
	}
	
	current_health = player->get_health();
}
