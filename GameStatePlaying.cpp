#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include "BlockFactory.h"
#include <assert.h>
#include <sstream>
#include <random>
#include <chrono>
#include <algorithm> 

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{	
		assert(font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));
		assert(eatAppleSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "AppleEat.wav"));
		assert(gameOverSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));
		assert(gameWinSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "WinSound.wav"));
		Platform::LoadTexture();
		Ball::LoadTexture();
		Block::LoadTexture();
		Bonus::LoadTexture();

		gameObjects.emplace_back(std::make_shared<Platform>());
		gameObjects.emplace_back(std::make_shared<Ball>());

		for (auto&& object : gameObjects)
		{
			object->Init();
		}

		factories.emplace(ObjectType::Simple, std::make_unique<SimpleBlockFactory>());
		factories.emplace(ObjectType::ThreeHit, std::make_unique<ThreeHitBlockFactory>());
		factories.emplace(ObjectType::Glass, std::make_unique<GlassBlockFactory>());

		CreatBlocks();

		background.setSize(sf::Vector2f(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 200, 0));

		eatAppleSound.setBuffer(eatAppleSoundBuffer);
		gameOverSound.setBuffer(gameOverSoundBuffer);
		gameWinSound.setBuffer(gameWinSoundBuffer);

		scoreStrategy = std::make_unique<SimpleScoreStrategy>();
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushGameState(GameStateType::ExitDialog, false);
			}
			else if (event.key.code == sf::Keyboard::F5)
			{
				Application::Instance().GetGame().saves.push(Save());
			}
			else if (event.key.code == sf::Keyboard::F9)
			{
				auto& game = Application::Instance().GetGame();
				if (!game.saves.empty())
				{
					Load(game.saves.top()); 
					game.saves.pop();
				}
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		auto platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		auto ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
		
		bool isGameFinished = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			platform->SetDirection(PlatformDirection::Right);
			platform->Update(timeDelta);
			if (!isGameStart)
			{
				ball->SetDirection(PlatformDirection::Right);
				ball->SetSpeedVector(Ball::GetBallDirectionVector(PlatformDirection::Right));
				ball->Update(timeDelta);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			platform->SetDirection(PlatformDirection::Left);
			platform->Update(timeDelta);
			if (!isGameStart)
			{
				ball->SetDirection(PlatformDirection::Left);
				ball->SetSpeedVector(Ball::GetBallDirectionVector(PlatformDirection::Left));
				ball->Update(timeDelta);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!isGameStart)
			{
				isGameStart = true;
				ball->SetSpeedVector(sf::Vector2f{ 200.f, -200.f });
				ball->speed = SETTINGS.BALL_SPEED;
			}
		}

		if (isGameStart)
		{
			ball->Update(timeDelta);
			platform->UpdateEffect(timeDelta);

			sf::Vector2f ballVec = ball->GetSpeedVector();

			sf::Vector2f ballPos = ball->GetPosition();

			if (ball->GetPosition().x <= 0 || ball->GetPosition().x >= SETTINGS.SCREEN_WIDTH)
			{
				ball->SetSpeedVector(sf::Vector2f{ -ballVec.x, ballVec.y });
			}
			else if (ball->GetPosition().y <= 0)
			{
				ball->SetSpeedVector(sf::Vector2f{ ballVec.x, -ballVec.y });
			}
			else if (ball->GetPosition().y >= SETTINGS.SCREEN_HEGHT)
			{
				isGameFinished = true;
			}

			platform->CheckCollision(ball);

			for (auto& obj : gameObjects)
			{
				auto block = std::dynamic_pointer_cast<Block>(obj);
				if (block && block->CheckCollision(ball))
				{
					if (rand() % 100 < 10 && block->GetHitCount() == 0)
					{  
						CreateBonus(obj->GetPosition());
					}

					if (block->GetHitCount() == 0)
					{
						totalScore += scoreStrategy->Calculate(block->GetType());
					}

					gameObjects.erase(
						std::remove_if(gameObjects.begin(), gameObjects.end(),
							[](const auto& obj) {
								auto block = std::dynamic_pointer_cast<Block>(obj);
								return block && block->GetHitCount() == 0;
							}),
						gameObjects.end()
					);
					break;
				}
			}
			
			for (int i = 0; i < bonuses.size(); i++)
			{
				bonuses[i]->Update(timeDelta);
				if (bonuses[i]->CheckCollision(platform))
				{
					bonuses[i]->ApplyEffect(*platform, *ball);
					bonuses.erase(bonuses.begin() + i);
					i--;
				}
				else if (bonuses[i]->GetPosition().y > SETTINGS.SCREEN_HEGHT)
				{
					bonuses.erase(bonuses.begin() + i);
					i--;
				}
			}
		}
		
		if (isGameFinished) 
		{
			gameOverSound.play();
			isGameStart = false;
			auto& game = Application::Instance().GetGame();
			game.recordsTable[SETTINGS.PLAYER_NAME] = std::max(game.recordsTable[SETTINGS.PLAYER_NAME], totalScore);
			game.PushGameState(GameStateType::GameOver, false);
		}
		else if (gameObjects.size() == 2)
		{
			gameWinSound.play();
			isGameStart = false;
			Application::Instance().GetGame().PushGameState(GameStateType::GameWin, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		window.draw(background);
		
		for (auto&& object : gameObjects)
		{
			object->Draw(window);
		}

		for (auto& bons : bonuses)
		{
			bons->Draw(window);
		}
	}

	void GameStatePlayingData::CreatBlocks()
	{
		const auto& level = levelloader.GetLevel(1);
		for (const auto& blockData : level.m_blocks)
		{
			sf::Vector2i blockPos = blockData.first;

			sf::Vector2f position{ SETTINGS.PLATFORM_WIDTH / 2.f + SETTINGS.PLATFORM_WIDTH * blockPos.x,
					SETTINGS.PLATFORM_HIGHT / 2 + SETTINGS.PLATFORM_HIGHT * (blockPos.y - 1) };

			gameObjects.emplace_back(factories.at(blockData.second)->CreateBlock(position));
			
		}
	}

	void GameStatePlayingData::CreateBonus(sf::Vector2f bonusPos)
	{
		std::vector<BonusType> types = 
		{
			BonusType::FastPlatform,
			BonusType::BigPlatform,
			BonusType::SlowBall
		};

		int index = rand() % types.size();
		BonusType randomType = types[index];

		std::shared_ptr<Bonus> bonus;

		switch (randomType) {
		case BonusType::FastPlatform:
			bonus = std::make_shared<BonusFastPlatform>();
			break;
		case BonusType::BigPlatform:
			bonus = std::make_shared<BonusBigPlatform>();
			break;
		case BonusType::SlowBall:
			bonus = std::make_shared<BonusSlowBallSpeed>();
			break;
		}

		bonus->Init();
		bonus->SetPosition(bonusPos);
		bonuses.push_back(bonus);
	}

	GameMemento GameStatePlayingData::Save()
	{
		auto ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
		BallSaveData ballData{
			ball->GetSaveData()
		};

		auto platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		PlatformSaveData platformData{
			platform->GetSaveData()
		};

		std::vector<BlockSaveData> blocksData;

		for (int i = 2; i < gameObjects.size(); i++)
		{
			auto block = std::dynamic_pointer_cast<Block>(gameObjects[i]);
			blocksData.push_back({ block->GetPosition(), block->GetType(), block->GetHitCount() });
		}

		std::vector<BonusSaveData> bonusesData;

		for (int i = 0; i < bonuses.size(); i++)
		{
			auto bonus = std::dynamic_pointer_cast<Bonus>(bonuses[i]);
			bonusesData.push_back({ bonus->GetPosition(), bonus->GetBonusType() });
		}

		return GameMemento(ballData, platformData, blocksData, bonusesData);
	}

	void GameStatePlayingData::Load(GameMemento& objects)
	{
		auto ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
		ball->LoadData(objects.ballData);

		auto platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		platform->LoadData(objects.platformData);

		gameObjects.clear();
		gameObjects.push_back(platform);
		gameObjects.push_back(ball);

		for (const auto& objData : objects.gameObjects)
		{
			std::shared_ptr<GameObject> obj;

			switch (objData.type)
			{
			case ObjectType::Simple:
				obj = std::make_shared<Block>(objData.position);
				break;
			case ObjectType::Glass:
				obj = std::make_shared<GlassBlock>(objData.position);
				break;
			case ObjectType::ThreeHit:
				obj = std::make_shared<DurableBlock>(objData.position);
				break;
			default:
				break;
			}

			auto block = std::dynamic_pointer_cast<Block>(obj);
			if (block)
			{
				block->SetHitCount(objData.hitCount);
			}

			gameObjects.push_back(obj);
		}

		bonuses.clear();
		for (const auto& objData : objects.bonusData)
		{
			std::shared_ptr<Bonus> obj;

			switch (objData.type)
			{
			case BonusType::FastPlatform:
				obj = std::make_shared<BonusFastPlatform>();
				break;
			case BonusType::BigPlatform:
				obj = std::make_shared<BonusBigPlatform>();
				break;
			case BonusType::SlowBall:
				obj = std::make_shared<BonusSlowBallSpeed>();
				break;
			default:
				break;
			}

			obj->Init();
			obj->SetPosition(objData.position);
			bonuses.push_back(obj);
		}
	}
}
