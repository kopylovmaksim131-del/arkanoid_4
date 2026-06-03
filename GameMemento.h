#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameObject.h"
#include "Bonus.h"

namespace ArkanoidGame
{
	struct BlockSaveData 
	{
		sf::Vector2f position;
		ObjectType type;      
		int hitCount;       
	};

	struct BonusSaveData
	{
		sf::Vector2f position;
		BonusType type;
	};

	class GameMemento
	{
		friend class GameStatePlayingData;

		BallSaveData ballData;
		PlatformSaveData platformData;
		std::vector<BlockSaveData> gameObjects;
		std::vector<BonusSaveData> bonusData;

	public:
		GameMemento(const BallSaveData ball,
			const PlatformSaveData platform,
			const std::vector<BlockSaveData> objects,
			const std::vector<BonusSaveData> bonuses)
			: ballData(ball),
			platformData(platform),
			gameObjects(objects),
			bonusData(bonuses) {};
	};
}
