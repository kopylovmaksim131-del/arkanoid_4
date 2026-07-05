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
		
		recordsTableTexts.reserve(SETTINGS.MAX_RECORDS_TABLE_SIZE);

		std::multimap<int, std::string> sortedRecordsTable;
		int playerScores = Application::Instance().GetGame().recordsTable[SETTINGS.PLAYER_NAME];
		for (const auto& item : Application::Instance().GetGame().recordsTable)
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isGameOver = false;
		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < SETTINGS.MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it)
		{
			recordsTableTexts.emplace_back(); // Create text in place
			sf::Text& text = recordsTableTexts.back();

			// We can use streams for writing into string and reading from it
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(font);
			text.setCharacterSize(24);
			if (it->second == SETTINGS.PLAYER_NAME)
			{
				text.setFillColor(sf::Color::Green);
				isGameOver = true;
			}
			else
			{
				text.setFillColor(sf::Color::White);
			}
		}

		if (!isGameOver)
		{
			sf::Text& text = recordsTableTexts.back();
			std::stringstream sstream;
			sstream << SETTINGS.MAX_RECORDS_TABLE_SIZE << ". " << SETTINGS.PLAYER_NAME << ": " << playerScores;
			text.setString(sstream.str());
			text.setFillColor(sf::Color::Green);
		}

		isGameOver = false;

		hintText.setFont(font);
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setString("Your score: " + std::to_string(playerScores));

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

		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 1.f }));
		hintText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 100.f);
		window.draw(hintText);

		std::vector<sf::Text*> textsList;
		textsList.reserve(recordsTableTexts.size());
		for (auto& text : recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2, viewSize.y / 1.5f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.f });

		sf::Text* hintText = &menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 200.f);
		window.draw(*hintText);

		menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}
