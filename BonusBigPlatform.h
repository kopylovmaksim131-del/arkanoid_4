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
#include "SizeEffect.h"

namespace ArkanoidGame
{
	class BonusBigPlatform : public Bonus
	{
	public:
		BonusBigPlatform();
		void ApplyEffect(Platform& platform, Ball& ball) override;

	private:
		void OnHit();
	};
}