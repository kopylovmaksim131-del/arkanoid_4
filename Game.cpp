#include "Game.h"
#include <assert.h>
#include <algorithm>
#include <memory>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateGameWin.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace ArkanoidGame
{
	Game::Game()
		: window(sf::VideoMode(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEGHT), SETTINGS.GAME_NAME)
	{
	}

	void Game::InitGame()
	{
		recordsTable =
		{
			{"John", 60},
			{"Jane", 50 },
			{"Alice", 40 },
			{"Bob", 30 },
			{"Clementine", 20 },
		};

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(GameStateType::MainMenu);
	}

	void Game::HandleWindowEvents()
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (gameStateStack.size() > 0)
			{
				HandleGameState(gameStateStack.back(), event);
			}
		}
	}

	bool Game::UpdateGame(float timeDelta)
	{
		if (gameStateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (gameStateStack.size() > 0)
			{
				ShutdownGameState(gameStateStack.back());
				gameStateStack.pop_back();
			}
		}
		else if (gameStateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (gameStateStack.size() > 0)
			{
				ShutdownGameState(gameStateStack.back());
				gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			gameStateStack.push_back({ pendingGameStateType, nullptr, pendingGameStateIsExclusivelyVisible });
			InitGameState(gameStateStack.back());
		}

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (gameStateStack.size() > 0)
		{
			UpdateGameState(gameStateStack.back(), timeDelta);
			return true;
		}

		return false;
	}

	void Game::DrawGame()
	{
		if (gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = gameStateStack.rbegin(); it != gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(**it);
			}
		}
	}

	void Game::ShutdownGame()
	{
		// Shutdown all game states
		while (gameStateStack.size() > 0)
		{
			ShutdownGameState(gameStateStack.back());
			gameStateStack.pop_back();
		}

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushGameState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		gameStateChangeType = GameStateChangeType::Push;
	}

	void Game::PopGameState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchGameState(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = GameStateChangeType::Switch;
	}

	void Game::InitGameState(GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			GameStateMainMenuData* data = new GameStateMainMenuData();
			data->Init();  
			state.data = data;
			break;
		}
		case GameStateType::Playing:
		{
			GameStatePlayingData* data = new GameStatePlayingData();
			data->Init(); 
			state.data = data;
			break;
		}
		case GameStateType::GameOver:
		{
			GameStateGameOverData* data = new GameStateGameOverData();
			data->Init(); 
			state.data = data;
			break;
		}
		case GameStateType::GameWin:
		{
			GameStateGameWinData* data = new GameStateGameWinData();
			data->Init();
			state.data = data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			GameStatePauseMenuData* data = new GameStatePauseMenuData();
			data->Init();  
			state.data = data;
			break;
		}
		case GameStateType::Records:
		{
			GameStateRecordsData* data = new GameStateRecordsData();
			data->Init(); 
			state.data = data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void Game::ShutdownGameState(GameState& state)
	{
		delete (GameStateData*)state.data;
		state.data = nullptr;
	}

	void Game::HandleGameState(GameState& state, sf::Event& event)
	{
		((GameStateData*)state.data)->HandleWindowEvent(event);
	}

	void Game::UpdateGameState(GameState& state, float timeDelta)
	{
		((GameStateData*)state.data)->Update(timeDelta);
	}

	void Game::DrawGameState(GameState& state)
	{
		((GameStateData*)state.data)->Draw(window);
	}

	bool Game::IsEnableOptions(GameOptions option)
	{
		bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	/*void Game::QuickSave(GameState& state)
	{
		if (state.type == GameStateType::Playing)
		{
			auto playingState = static_cast<GameStatePlayingData*>(state.data);
			saves.push(playingState->Save());
		}
		
	}

	void Game::QuickLoad(GameState& state)
	{
		if (state.type == GameStateType::Playing && saves.size() > 0)
		{
			auto playingState = static_cast<GameStatePlayingData*>(state.data);
			playingState->Load(saves.top());
		}
	}*/
}
