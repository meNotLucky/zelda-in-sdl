#include "SpriteManager.h"
#include "Sprite.h"
#include "Animation.h"
#include <SDL_image.h>

SpriteManager::SpriteManager(SDL_Renderer * p_renderer)
{
	if (p_renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SpriteManager::SpriteManager found no constructor: %s", SDL_GetError());
	}
	else {
		m_renderer = p_renderer;
	}
}

SpriteManager::~SpriteManager()
{
	for (Sprite* sprite : m_sprites) {
		delete sprite;
		sprite = nullptr;
	}
	m_sprites.clear();

	for (auto pair : m_textures) {
		SDL_DestroyTexture(pair.second);
		pair.second = nullptr;
	}
	m_textures.clear();

	m_renderer = nullptr;
}

Sprite * SpriteManager::create_sprite(const char * p_filePath, int p_x, int p_y, int p_w, int p_h)
{
	auto it = m_textures.find(p_filePath);
	if (it == m_textures.end())
	{
		SDL_Surface* surface = IMG_Load(p_filePath);
		if (surface == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load surface: %s", SDL_GetError());
			return nullptr;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);
		m_textures[p_filePath] = texture;
		Sprite* sprite = new Sprite(texture, p_x, p_y, p_w, p_h);
		m_sprites.push_back(sprite);
		return sprite;
	}
	else
	{
		Sprite* sprite = new Sprite(m_textures[p_filePath], p_x, p_y, p_w, p_h);
		return sprite;
	}
}

Animation* SpriteManager::create_animation(const char* p_filePath, int p_x, int p_y, int p_w, int p_h) {

	auto it = m_textures.find(p_filePath);
	if (it == m_textures.end())
	{
		SDL_Surface* surface = IMG_Load(p_filePath);
		if (surface == nullptr)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load surface: %s", SDL_GetError());
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);
		m_textures[p_filePath] = texture;
		Animation* animation = new Animation(texture, p_x, p_y, p_w, p_h);
		m_animations.push_back(animation);
		return animation;
	}
	else
	{
		Animation* animation = new Animation(m_textures[p_filePath], p_x, p_y, p_w, p_h);
		return animation;
	}
}

Sprite * SpriteManager::create_text(const char * p_fontPath, std::string p_text, SDL_Color p_color, int p_x, int p_y, int p_w, int p_h)
{
	TTF_Font* font = TTF_OpenFont(p_fontPath, 28);
	SDL_Surface* surface = TTF_RenderText_Solid(font, p_text.c_str(), p_color);
	if (surface == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load surface: %s", SDL_GetError());
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);
	m_textures[p_fontPath] = texture;
	Sprite* sprite = new Sprite(texture, p_x, p_y, p_w, p_h);
	m_sprites.push_back(sprite);
	return sprite;
}
