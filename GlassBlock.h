#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "Block.h"

namespace ArkanoidGame
{
	class GlassBlock : public Block
	{
	public:
		GlassBlock(const sf::Vector2f& blockPosition);

		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;
	};
}
