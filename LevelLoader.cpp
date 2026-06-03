#include "LevelLoader.h"
#include "GameSettings.h"

#include <assert.h>
#include <fstream>
#include <filesystem>

namespace ArkanoidGame
{
	Level& LevelLoader::GetLevel(int i)
	{
		return levels.at(i);
	}

	int LevelLoader::GetLevelCount()
	{
		return levels.size();
	}

	void LevelLoader::LoadLevelFromFile()
	{
		std::string filepath = SETTINGS.LEVELS_PATH;
		std::string line;
		std::ifstream file(filepath);

		int y = 0;

		while (getline(file, line))
		{
			if (line.rfind("level", 0) == 0)
			{
				auto level = std::stoi(line.substr(6, line.size() - 6));
				levels.emplace_back(Level());
				y = 0;
			}
			else
			{
				int x = 0;
				for (char c : line)
				{
					if (c != ' ')
					{
						levels.back().m_blocks.emplace_back(std::make_pair(sf::Vector2i { x ,y }, CharToBlockType(c)));
					}
					++x;
				}
			}
			++y;
		}

		file.close();

	}

	ObjectType LevelLoader::CharToBlockType(char symbol)
	{
		ObjectType blockType;

		switch (symbol)
		{
		case '0':
			blockType = ObjectType::Glass;
			break;
		case '1':
			blockType = ObjectType::Simple;
			break;
		case '2':
			blockType = ObjectType::ThreeHit;
			break;
		default:
			assert(false);
			break;
		}
		return blockType;
	}
}