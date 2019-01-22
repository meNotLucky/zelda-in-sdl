#include "Animation.h"

Animation::Animation(SDL_Texture * p_texture, int p_x, int p_y, int p_w, int p_h)
{
	m_texture = p_texture;

	//Set sprite clips
	m_spriteClips[0].x = p_x;
	m_spriteClips[0].y = p_y;
	m_spriteClips[0].w = p_w;
	m_spriteClips[0].h = p_h;

	m_spriteClips[1].x = p_x + p_w;
	m_spriteClips[1].y = p_y;
	m_spriteClips[1].w = p_w;
	m_spriteClips[1].h = p_h;

	m_spriteClips[2].x = p_x + p_w * 2;
	m_spriteClips[2].y = p_y;
	m_spriteClips[2].w = p_w;
	m_spriteClips[2].h = p_h;

	m_spriteClips[3].x = p_x + p_w * 3;
	m_spriteClips[3].y = p_y;
	m_spriteClips[3].w = p_w;
	m_spriteClips[3].h = p_h;
}

bool Animation::render_animation(SDL_Renderer* p_renderer, int playback_speed, bool loop, SDL_Rect* p_rect)
{
	if (!loop) {
		bool reset = true;

		if (!has_reset) {
			if (reset) {
				has_reset = true;
				frame = 0;
			}
		}
	}

	SDL_Rect* currentClip = &m_spriteClips[frame / playback_speed];
	SDL_RenderCopy(p_renderer, m_texture, currentClip, p_rect);
		
	if (loop) {
		frame++;
		if (frame / playback_speed >= 4) {
			frame = 0;
		}
	}
	else if (!loop) {
		if (frame / playback_speed < 4) {
			frame++;
		}
		else {
			has_reset = false;
			return false;
		}
	}

	return true;
}

SDL_Texture* Animation::get_texture()
{
	return m_texture;
}


