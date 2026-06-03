#include "Application.h"
#include <cstdlib>

namespace ArkanoidGame
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	//Application::Application() :
	//	window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEGHT), GAME_NAME)
	Application::Application()
	{
		// Init random number generator
		unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
		srand(seed);

		//InitGame(game);
		game.InitGame();
	}

	Application::~Application()
	{
		game.ShutdownGame();
	}

	void Application::Run()
	{
		// Init game clock
		sf::Clock gameClock;

		// Game loop
		while (game.window.isOpen()) {

			float startTime = gameClock.getElapsedTime().asSeconds();

			game.HandleWindowEvents();

			if (!game.window.isOpen()) {
				break;
			}

			if (game.UpdateGame(SETTINGS.TIME_PER_FRAME))
			{
				// Draw everything here
				// Clear the window first
				game.window.clear();

				game.DrawGame();

				// End the current frame, display window contents on screen
				game.window.display();
			}
			else
			{
				game.window.close();
			}

			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < SETTINGS.TIME_PER_FRAME) {
				// Reduce framerate to not spam CPU and GPU
				sf::sleep(sf::seconds(SETTINGS.TIME_PER_FRAME - deltaTime));
			}
		}
	}

}