#include "DurableBlock.h"

namespace ArkanoidGame
{
	DurableBlock::DurableBlock(const sf::Vector2f& blockPosition) : Block(blockPosition)
	{
		hitCount = 3;
		type = ObjectType::ThreeHit;
	}

	void DurableBlock::OnHit()
	{
		hitCount -= 1;
		sprite.setColor(blockColors[hitCount]);
		if (hitCount == 0) {
			notifyObservers();
		}
	}
}
