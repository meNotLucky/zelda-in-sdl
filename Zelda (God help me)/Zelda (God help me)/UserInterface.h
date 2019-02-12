#pragma once
#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "Player.h"
#include "Sword.h"

class UsierInterface {

	SDL_Rect m_rect;
	Sprite* m_layout;
	std::vector<Sprite*> m_hearts;
	std::vector<SDL_Rect> m_rects;
	SDL_Rect hearts_1_rect, hearts_2_rect, hearts_3_rect, hearts_4_rect, hearts_5_rect, hearts_6_rect;
	int current_health;
	Sword* m_sword;
	bool sword_aquired;
	Sprite* m_rupee_count;

public:
	UsierInterface();
	~UsierInterface();
	void render(SDL_Renderer* p_renderer);
	void update(Player* player);
};