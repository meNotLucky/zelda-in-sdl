#include "SystemManager.h"
#include "Config.h"
#include "Service.h"
#include "ErrorLogger.h"
#include "InputManager.h"

SystemManager::SystemManager()
{
	running = true;
	quit_event = false;
}

SystemManager::~SystemManager()
{
	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);
	if (window != nullptr)
		SDL_DestroyWindow(window);

	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void SystemManager::init_system()
{
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		Service<ErrorLogger>::Get()->log_error("", SDL_GetError());

	// Init SDL_Mix
	if (Mix_Init(MIX_INIT_MP3) == 0)
		Service<ErrorLogger>::Get()->log_error("_Mix", Mix_GetError());

	// Open Audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		Service<ErrorLogger>::Get()->log_error("_Mix", Mix_GetError());

	// Init SDL_Image
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
		Service<ErrorLogger>::Get()->log_error("_Image", IMG_GetError());

	// Init SDL_ttf
	if(TTF_Init() == -1)
		Service<ErrorLogger>::Get()->log_error("_ttf", TTF_GetError());

	// Create window
	window = SDL_CreateWindow("The Legend of Zelda", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Config::SCREENMODE == FULLSCREEN ? SDL_WINDOW_FULLSCREEN : Config::SCREENMODE == BORDERLESS ? SDL_WINDOW_BORDERLESS | SDL_WINDOW_MAXIMIZED : Config::SCREENMODE == WINDOWED ? 0 : 0);
	if (window == nullptr)
		Service<ErrorLogger>::Get()->log_error("", SDL_GetError());

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
		Service<ErrorLogger>::Get()->log_error("", SDL_GetError());

	// Set Window Hint
	if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0") == SDL_FALSE) {
		Service<ErrorLogger>::Get()->log_error("", SDL_GetError());
	}

	// Create Window Icon
	SDL_Surface* surface = IMG_Load("Assets/Sprites/window_icon.png");
	if (surface == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load surface: %s", SDL_GetError());

	SDL_SetWindowIcon(window, surface);
	SDL_FreeSurface(surface);

}

void SystemManager::update()
{
	if (Service<InputManager>::Get()->key_pressed(SDL_SCANCODE_ESCAPE))
		running = false;

	if (quit_event)
		running = false;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
	SDL_RenderClear(renderer);
}
