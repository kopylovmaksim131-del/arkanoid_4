#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Platform.h"
#include "Collidable.h"


namespace ArkanoidGame
{
	class Block;

	struct BallSaveData
	{
		sf::Vector2f position;
		PlatformDirection direction;
		sf::Vector2f speedVector;
		float speedMultiplier;
		float speedMultiplierTimer;
		float speedMultiplierDuration;
	};

	class Ball : public GameObject, public Collidable
	{
	public:
		void Init() override;
		void Draw(sf::RenderWindow& window) override;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;

		static sf::Texture* texture;
		static void LoadTexture();
		static sf::Vector2f GetBallDirectionVector(PlatformDirection dir);

		void SetDirection(PlatformDirection dir);
		void SetSpeedVector(const sf::Vector2f& v);
		void SetCollisionParam(bool isPlatform, float platformPos, bool isGlassBlock);
		void SetSpeedMultiplier(float multiplier, float duration);
		BallSaveData GetSaveData();
		void LoadData(const BallSaveData saveData);
		sf::Vector2f GetSpeedVector();

		float speed = 0.f;

	private:
		void OnHit();
		void CheckBonusEffect(float timeDelta);
		PlatformDirection direction = PlatformDirection::Right;
		sf::Vector2f pos{ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEGHT - 20.f - SETTINGS.BALL_SIZE / 2.f - SETTINGS.PLATFORM_HIGHT / 2.f };
		sf::Vector2f speedVector{ 0.f, 0.f };
		bool isCollisionWithPlatform = false;
		bool isCollisionWithGlassBlock = false;
		float platformPosX = 0.f;
		float speedMultiplier = 1.0f;
		float speedMultiplierTimer = 0.0f;
		float speedMultiplierDuration = 0.0f;
	};
}
