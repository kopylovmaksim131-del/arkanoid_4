#include "BlockFactory.h"
#include "Block.h"
#include "DurableBlock.h"
#include "GlassBlock.h"


namespace ArkanoidGame
{
	int BlockFactory::GetCreatBreackableBlockCount()
	{
		return CreatBreackableBlockCount;
	}
	void BlockFactory::ClearCounter()
	{
		CreatBreackableBlockCount = 0;
	}

	std::shared_ptr<Block> SimpleBlockFactory::CreateBlock(const sf::Vector2f position)
	{
		return std::make_shared<Block>(position);
	}

	std::shared_ptr<Block> ThreeHitBlockFactory::CreateBlock(const sf::Vector2f position)
	{
		return std::make_shared<DurableBlock>(position);
	}

	std::shared_ptr<Block> GlassBlockFactory::CreateBlock(const sf::Vector2f position)
	{
		return std::make_shared<GlassBlock>(position);
	}
}