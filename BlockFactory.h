#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArkanoidGame
{
	class Block;

	class BlockFactory
	{
	protected:
		int CreatBreackableBlockCount = 0;

	public:
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f position) = 0;
		virtual ~BlockFactory() = default;
		int GetCreatBreackableBlockCount();
		void ClearCounter();
	};

	class SimpleBlockFactory final : public BlockFactory
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f position) override;
		~SimpleBlockFactory() override = default;
	};

	class ThreeHitBlockFactory final : public BlockFactory
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f position) override;
		~ThreeHitBlockFactory() override = default;
	};

	class GlassBlockFactory final : public BlockFactory
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f position) override;
		~GlassBlockFactory() override = default;
	};
}