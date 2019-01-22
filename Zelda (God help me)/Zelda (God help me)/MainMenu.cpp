#include "MainMenu.h"
#include "Service.h"
#include "Config.h"

Menu::Menu(SDL_Renderer* p_renderer)
{
	m_id = "Menu";
	m_nextState = "Game";

	m_renderer = p_renderer;
}

void Menu::enter()
{
	timer = 0;

	r = 255; g = 255; b = 255;

	title_rect.x = 0; title_rect.y = 0; title_rect.w = Config::SCREEN_WIDTH; title_rect.h = Config::SCREEN_HEIGHT;
	story_rect.x = 0; story_rect.y = Config::SCREEN_HEIGHT; story_rect.w = Config::SCREEN_WIDTH; story_rect.h = 3905;
	waterfall_rect.x = 320; waterfall_rect.y = 700; waterfall_rect.w = 128; waterfall_rect.h = 264;

	title_animation = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Intro/title_anim.png", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	title_still = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Intro/title_still.png", 0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
	story_items = Service<SpriteManager>::Get()->create_sprite("Assets/Sprites/Intro/story_items.png", 0, 0, Config::SCREEN_WIDTH, 3905);

	waterfall_animation = Service<SpriteManager>::Get()->create_animation("Assets/Sprites/Intro/waterfall_anim.png", 0, 0, 128, 272);

	intro_music = Service<AudioManager>::Get()->create_music("Assets/Audio/Music/intro.mp3");

	if(intro_music != NULL)
		intro_music->play_music(-1);

	std::cout << "STATE ENTERED: Main Menu" << std::endl;
}

void Menu::exit() {
	if (intro_music != NULL)
		Service<AudioManager>::Get()->stop_music();
}

bool Menu::update()
{

	if (Service<InputManager>::Get()->key_pressed(SDL_SCANCODE_RETURN)) {
		m_nextState = "Game";
		return false;
	}

	if (timer > 9) {
		if (timer < 14) {
			if (r > 0) { r -= 15; g -= 15; }
			else { r = 0; g = 0; }
		}
		else {
			if (b > 0) { b -= 15; }
			else { r = 0; g = 0; b = 0; }
		}
	}

	SDL_SetTextureColorMod(title_animation->get_texture(), r, g, b);
	SDL_SetTextureColorMod(title_still->get_texture(), r, g, b);
	SDL_SetTextureColorMod(waterfall_animation->get_texture(), r, g, b);

	if (timer < 9)
		title_animation->render_animation(m_renderer, 12, true, &title_rect);
	else
		SDL_RenderCopy(m_renderer, title_still->get_texture(), &title_still->get_area(), &title_rect);

	waterfall_animation->render_animation(m_renderer, 6, true, &waterfall_rect);

	SDL_RenderCopy(m_renderer, story_items->get_texture(), &story_items->get_area(), &story_rect);

	if (timer > 16) {
		if (story_rect.y > -3100) {
			story_y -= 1.1f;
			story_rect.y = (int)story_y;
		}
	}

	if (timer > 82.5f) {
		m_nextState = "Menu";
		return false;
	}

	timer += 1.0f / 60;

	return true;
}
