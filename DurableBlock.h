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
	class DurableBlock : public Block
	{
	public:
		DurableBlock(const sf::Vector2f& blockPosition);
	private:
		void OnHit() override;
		std::vector<sf::Color> blockColors { sf::Color::White, sf::Color::Red, sf::Color::Yellow };
	};
}
