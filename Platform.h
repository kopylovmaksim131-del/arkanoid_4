#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Collidable.h"

namespace ArkanoidGame
{
	struct PlatformSaveData
	{
		sf::Vector2f position;
		float speedMultiplier;
		float speedMultiplierTimer;
		float speedMultiplierDuration;

		float sizeMultiplier;
		float sizeMultiplierTimer;
		float sizeMultiplierDuration;
		bool sizeEffectSet;
	};

	class Ball;

	enum class PlatformDirection
	{
		Right = 0,
		Left
	};

	class Platform : public GameObject, public Collidable
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;

		void SetDirection(PlatformDirection dir);
		void UpdateEffect(float timeDelta);
		void SetSizeMultiplier(float multiplier, float duration);
		void SetSpeedMultiplier(float multiplier, float duration);
		PlatformSaveData GetSaveData();
		void LoadData(const PlatformSaveData saveData);
		static sf::Texture* texture;
		static void LoadTexture();
		static sf::Vector2f GetPlatformDirectionVector(PlatformDirection dir);

	private:
		void OnHit();
		void SetNewScale();
		float speed = 0.f; 
		PlatformDirection direction = PlatformDirection::Right;
		sf::Vector2f pos { SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEGHT - 20.f };
		float speedMultiplier = 1.0f;
		float speedMultiplierTimer = 0.0f;
		float speedMultiplierDuration = 0.0f;

		float sizeMultiplier = 1.0f;
		float sizeMultiplierTimer = 0.0f;
		float sizeMultiplierDuration = 0.0f;
		bool sizeEffectSet = false;
	};
}
