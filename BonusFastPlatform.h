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
#include "Collidable.h"
#include "SpeedEffectPlatform.h"

namespace ArkanoidGame
{
	class BonusFastPlatform : public Bonus
	{
	public:
		BonusFastPlatform();
		void ApplyEffect(Platform& platform, Ball& ball) override;

	private:
		void OnHit();
	};
}