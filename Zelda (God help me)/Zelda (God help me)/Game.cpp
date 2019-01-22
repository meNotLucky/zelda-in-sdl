#include "Game.h"
#include "Service.h"
#include "CollisionManager.h"
#include "Config.h"
#include <fstream>

Game::Game(SDL_Renderer * p_renderer)
{

	m_id = "Game";
	m_nextState = "Death";
	m_music = Service<AudioManager>::Get()->create_music("Assets/Audio/Music/overworld.mp3");

	m_renderer = p_renderer;
}

void Game::enter()
{
	m_ui = new UsierInterface;
	player.reset_player();
	Service<WorldManager>::Get()->reset_world(1);

	Service<WorldManager>::Get()->add_level(1, LEVEL_OVERWORLD, 0, 256, 0, WALKING, true);
	Service<WorldManager>::Get()->add_level(2, LEVEL_OVERWORLD, 1024, 256, 4, WALKING, true);
	Service<WorldManager>::Get()->add_level(3, LEVEL_OVERWORLD, -1024, 256, 4, WALKING, true);
	Service<WorldManager>::Get()->add_level(4, LEVEL_OVERWORLD, 0, -448, 4, WALKING, true);
	Service<WorldManager>::Get()->add_level(5, LEVEL_CAVE, 0, 256, 0, WALKING, false);

	if (m_music != nullptr)
		m_music->play_music(-1);

	ui_background.x = 0; ui_background.y = 0;
	ui_background.w = Config::SCREEN_WIDTH; ui_background.h = 256;

	std::cout << "STATE ENTERED: Game" << std::endl;
}

void Game::exit() {
	
	Service<AudioManager>::Get()->stop_music();
	delete m_ui;
	m_ui = nullptr;
}

bool Game::update()
{

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 1);

	Service<WorldManager>::Get()->update_world(&player);
	player.update();

	if (player.player_death()) {
		if (Service<WorldManager>::Get()->on_player_death(m_renderer, &player))
			return false;
	}

	Service<WorldManager>::Get()->render_world(m_renderer);
	player.render(m_renderer);


	SDL_SetRenderDrawColor(m_renderer, 0,0,0,1);
	SDL_RenderFillRect(m_renderer, &ui_background);
	m_ui->update(&player);
	m_ui->render(m_renderer);
	return true;
}
