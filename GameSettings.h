#pragma once
#include <string>

namespace ArkanoidGame
{
	class GameWorld
	{
	private:
		GameWorld() = default;
	public:
		static GameWorld& Inctance()
		{
			static GameWorld gameWorld;
			return gameWorld;
		}

		// Resources path
		const std::string RESOURCES_PATH = "Resources/";
		const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
		const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
		const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
		const std::string LEVELS_PATH = RESOURCES_PATH + "levels.config";

		// Game settings constants
		const float PLATFORM_HIGHT = 20.f;
		const float PLATFORM_WIDTH = 80.f;
		const float BLOCK_HIGHT = 16.f;
		const float BLOCK_WIDTH = 76.f;
		const float BALL_SIZE = 20.f;
		const float BALL_SPEED = 30.f;
		const float BONUS_SIZE = 20.f;
		const float INITIAL_SPEED = 500.f;
		const unsigned int SCREEN_WIDTH = 800;
		const unsigned int SCREEN_HEGHT = 600;
		const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

		const int MAX_RECORDS_TABLE_SIZE = 5;
		//static const char* PLAYER_NAME; // We need to define this constant in some CPP
		const std::string PLAYER_NAME = "Player";
		const std::string GAME_NAME = "ArkanoidGame";
	};
}

#define SETTINGS GameWorld::Inctance()
