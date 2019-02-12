#pragma comment(lib, "../Dependencies/SDL2/lib/x64/SDL2.lib")
#pragma comment(lib, "../Dependencies/SDL2/lib/x64/SDL2main.lib")
#pragma comment(lib, "../Dependencies/SDL2_mixer/lib/x64/SDL2_mixer.lib")
#pragma comment(lib, "../Dependencies/SDL2_image/lib/x64/SDL2_image.lib")
#pragma comment(lib, "../Dependencies/SDL2_ttf/lib/x64/SDL2_ttf.lib")


#include <iostream>
#include <ctime>

#include "Service.h"

// Managers
#include "SystemManager.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "CollisionManager.h"
#include "WorldManager.h"
#include "ErrorLogger.h"

// States
#include "MainMenu.h"
#include "Game.h"
#include "Death.h"

#undef main

int main() {

	SystemManager system;
	system.init_system();
	
	{
		SpriteManager spriteManager(system.renderer);
		CollisionManager collisionManager;
		InputManager inputManager;
		AudioManager audioManager;
		WorldManager worldManager(1);
		ErrorLogger errorLogger;

		Service<SpriteManager>::Set(&spriteManager);
		Service<CollisionManager>::Set(&collisionManager);
		Service<InputManager>::Set(&inputManager);
		Service<AudioManager>::Set(&audioManager);
		Service<WorldManager>::Set(&worldManager);
		Service<ErrorLogger>::Set(&errorLogger);

		FSM stateMachine;
		Menu menu(system.renderer);
		Game game(system.renderer);
		Death death(system.renderer);
		stateMachine.add_state(&menu);
		stateMachine.add_state(&game);
		stateMachine.add_state(&death);
		stateMachine.set_state("Menu");

		while (system.running == true) {

			srand((unsigned int)time(NULL));

			// System updates
			system.update();

			// Input uptades
			inputManager.update_events();

			// Updates FSM
			stateMachine.update();

			// Render
			SDL_RenderPresent(system.renderer);
		}

	}

	return 0;
}