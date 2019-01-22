#include "Death.h"
#include "Service.h"
#include "SpriteManager.h"
#include "InputManager.h"

Death::Death(SDL_Renderer * p_renderer)
{
	m_id = "Death";
	m_nextState = "Game";

	m_renderer = p_renderer;

	m_screen_rect.x = 0; m_screen_rect.y = 0;
	m_screen_rect.w = 1024; m_screen_rect.h = 960;
	m_end_screen = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/EndScreen/screen.png", 0, 0, 1024, 960);
	m_music = Service<AudioManager>::Get()->create_music("Assets/Audio/Music/GameOver.mp3");
}

void Death::enter()
{
	std::cout << "STATE ENTERED: Death" << std::endl;
	if(m_music != nullptr)
		m_music->play_music(-1);
}

void Death::exit()
{
	Service<AudioManager>::Get()->stop_music();
}

bool Death::update()
{
	if(m_end_screen != nullptr)
		SDL_RenderCopy(m_renderer, m_end_screen->get_texture(), &m_end_screen->get_area(), &m_screen_rect);

	if (Service<InputManager>::Get()->key_pressed(SDL_SCANCODE_RETURN))
		return false;

	return true;
}
