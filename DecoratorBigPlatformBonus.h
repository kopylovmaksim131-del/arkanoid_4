#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "DecoratorBonus.h"

namespace ArkanoidGame
{
	class DecoratorBigPlatformBonus : public DecoratorBonus
	{
	public:
		DecoratorBigPlatformBonus(std::shared_ptr<GameObject> obj) : DecoratorBonus(std::move(obj)) {}


	};
}