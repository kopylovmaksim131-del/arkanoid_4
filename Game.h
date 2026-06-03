#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "Sprite.h"
#include "GameSettings.h"
#include "GameMemento.h"
#include <unordered_map>
#include <stack>

namespace ArkanoidGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
		GameWin
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		void InitGame();
		void HandleWindowEvents();
		bool UpdateGame(float timeDelta); // Return false if game should be closed
		void DrawGame();
		void ShutdownGame();
		void PushGameState(GameStateType stateType, bool isExclusivelyVisible);
		void PopGameState();
		void SwitchGameState(GameStateType newState);
		void InitGameState(GameState& state);
		void ShutdownGameState(GameState& state);
		void HandleGameState(GameState& state, sf::Event& event);
		void UpdateGameState(GameState& state, float timeDelta);
		void DrawGameState(GameState& state);
		bool IsEnableOptions(GameOptions option);
		//void QuickSave(GameState& state);
		//void QuickLoad(GameState& state);
		Game();

	public:
		std::unordered_map<std::string, int> recordsTable;
		GameOptions options = GameOptions::Default;
		sf::RenderWindow window;
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;
		std::stack<GameMemento> saves;
	};
}
