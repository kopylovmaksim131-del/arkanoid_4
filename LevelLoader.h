#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "GameObject.h"
#include "Block.h"

namespace ArkanoidGame
{
	struct Level
	{
		std::vector<std::pair<sf::Vector2i, ObjectType>> m_blocks;
	};

	class LevelLoader
	{
	public:
		LevelLoader() { LoadLevelFromFile(); };
		Level& GetLevel( int i);
		~LevelLoader() = default;
		int GetLevelCount();

	private:
		void LoadLevelFromFile();

		static ObjectType CharToBlockType(char symbol);
		std::vector<Level> levels;
	};
}