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
#include "BonusEffect.h"


namespace ArkanoidGame
{
	//class Block;
	enum class BonusType
	{
		FastPlatform,
		BigPlatform,
		SlowBall
	};

	class Bonus : public GameObject, public Collidable
	{
	public:
		void Init() override;
		void Draw(sf::RenderWindow& window) override;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;

		virtual void ApplyEffect(Platform& platform, Ball& ball);

		BonusType GetBonusType();

		static sf::Texture* texture;
		static void LoadTexture();

	protected:
		BonusType bonusType;
		std::unique_ptr<BonusEffect> effect;

	private:
		//void OnHit();
		float speed = SETTINGS.INITIAL_SPEED / 2.f;
	};
}