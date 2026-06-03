#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "Bonus.h"
#include "GameObject.h"
#include "Platform.h"
#include "Ball.h"
#include "SpeedEffect.h"
#include "Collidable.h"

namespace ArkanoidGame
{
	class BonusSlowBallSpeed : public Bonus
	{
	public:
		BonusSlowBallSpeed();
		void ApplyEffect(Platform& platform, Ball& ball) override;

	private:
		void OnHit();
	};
}