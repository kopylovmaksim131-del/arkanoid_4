#include "GameStateGameWin.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStateGameWinData::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		timeSinceGameOver = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200; 
		background.setFillColor(backgroundColor);

		gameOverText.setFont(font);
		gameOverText.setCharacterSize(48);
		gameOverText.setStyle(sf::Text::Bold);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setString("CONGRATULATE");

		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(font);
		yesItem.text.setCharacterSize(24);
		yesItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().SwitchGameState(GameStateType::Playing);
			};

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(font);
		noItem.text.setCharacterSize(24);
		noItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().SwitchGameState(GameStateType::MainMenu);
			};

		MenuItem mainMenu;
		mainMenu.hintText.setString("Play again?");
		mainMenu.hintText.setFont(font);
		mainMenu.hintText.setCharacterSize(48);
		mainMenu.hintText.setFillColor(sf::Color::Red);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 10.f;
		mainMenu.childrens.push_back(yesItem);
		mainMenu.childrens.push_back(noItem);

		menu.Init(mainMenu);
	}

	void GameStateGameWinData::HandleWindowEvent(const sf::Event& event)
	{
		Game& game = Application::Instance().GetGame();
		if (event.type == sf::Event::KeyPressed)
		{
		
			if (event.key.code == sf::Keyboard::Enter)
			{
				menu.PressOnSelectedItem();
			}

			Orientation orientation = menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu.SwitchToNextMenuItem();
			}
		}
	}

	void GameStateGameWinData::Update(float timeDelta)
	{
		timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		gameOverText.setFillColor(gameOverTextColor);

	}

	void GameStateGameWinData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background.setOrigin(0.f, 0.f);
		background.setSize(viewSize);
		window.draw(background);

		gameOverText.setOrigin(GetTextOrigin(gameOverText, { 0.5f, 1.f }));
		gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 150.f);
		window.draw(gameOverText);

		sf::Text* hintText = &menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 200.f);
		window.draw(*hintText);

		menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}
