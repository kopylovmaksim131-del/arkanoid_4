#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "DurableBlock.h"
#include "GlassBlock.h"
#include "Bonus.h"
#include "BonusSlowBallSpeed.h"
#include "BonusFastPlatform.h"
#include "BonusBigPlatform.h"
#include "GameStateData.h"
#include "LevelLoader.h"
#include "BlockFactory.h"
#include "GameMemento.h"
#include "SimpleScoreStrategy.h"
#include <unordered_map>

namespace ArkanoidGame
{
	class Game;

	class GameStatePlayingData: public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

		void CreatBlocks();
		void CreateBonus(sf::Vector2f bonusPos);

		GameMemento Save();
		void Load(GameMemento& objects);

	private:
		sf::Font font;
		sf::Texture platformTex;
		sf::Texture ballTex;
		sf::Texture blockTex;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer gameWinSoundBuffer;

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Bonus>> bonuses;

		std::unique_ptr<SimpleScoreStrategy> scoreStrategy;
		int totalScore = 0;

		sf::RectangleShape background;

		LevelLoader levelloader;

		// Sounds
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
		sf::Sound gameWinSound;

		std::unordered_map <ObjectType, std::unique_ptr<BlockFactory>> factories;

		bool isGameStart = false;
	};
	
}
