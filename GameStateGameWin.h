#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "GameStateData.h"

namespace ArkanoidGame
{
	class Game;

	class GameStateGameWinData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;
		sf::Font font;
		float timeSinceGameOver = 0.f;
		Menu menu;
	};
}
