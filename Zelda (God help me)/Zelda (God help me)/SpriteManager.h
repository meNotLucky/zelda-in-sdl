/*

SPRITE MANAGER

The sprite manager is used to add and re-use sprites, animation and text in the game.
It uses the SDL textures and stores them in a map. Depending on what type of object was created (Sprite, Animation or Text),
it will be rendered in a different way.

This was created to make sure no sprites had to be added more than once and take up more space.
It also gives a simple way of giving a game object a texture or animation.

*/

#pragma once

#include <map>
#include <vector>
#include <SDL_ttf.h>

class Sprite;
class Animation;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Color;

class SpriteManager
{
	SDL_Renderer* m_renderer;
	std::map<const char*, SDL_Texture*> m_textures;
	std::vector<Sprite*> m_sprites;
	std::vector<Animation*> m_animations;

public:
	SpriteManager(SDL_Renderer* p_renderer);
	~SpriteManager();
	Sprite* create_sprite(const char* p_filePath, int p_x, int p_y, int p_w, int p_h);
	Animation* create_animation(const char* p_filePath, int p_x, int p_y, int p_w, int p_h);
	Sprite* create_text(const char * p_fontPath, std::string p_text, SDL_Color p_color, int p_x, int p_y, int p_w, int p_h);

};