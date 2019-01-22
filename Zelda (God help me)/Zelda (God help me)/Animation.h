#pragma once

#include <SDL.h>

class Animation {

	SDL_Texture* m_texture;
	SDL_Rect m_spriteClips[4];

	int frame = 0;
	bool has_reset = false;

public:
	Animation(SDL_Texture* p_texture, int p_x, int p_y, int p_w, int p_h);
	bool render_animation(SDL_Renderer* p_renderer, int playback_speed, bool loop, SDL_Rect* p_rect);
	SDL_Texture* get_texture();
};