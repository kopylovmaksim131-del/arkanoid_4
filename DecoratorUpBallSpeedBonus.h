#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "DecoratorBonus.h"
#include "Ball.h"

namespace ArkanoidGame
{
	class DecoratorUpBallSpeedBonus : public DecoratorBonus
	{
	public:
		DecoratorUpBallSpeedBonus(std::shared_ptr<GameObject> obj) : DecoratorBonus(std::move(obj)) {}

	private:
		float speedMultiplier = 0.5f;

		void Update(float deltaTime) override;
	};
}