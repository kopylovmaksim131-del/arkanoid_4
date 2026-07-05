#include "Block.h"
#include "Ball.h"

namespace ArkanoidGame
{
	sf::Texture* Block::texture = nullptr;

	void Block::LoadTexture()
	{
		texture = new sf::Texture();
		assert(texture->loadFromFile(SETTINGS.TEXTURES_PATH + "Block.png"));
	}

	Block::Block(const sf::Vector2f& blockPosition)
	{
		InitSprite(sprite, SETTINGS.BLOCK_WIDTH, SETTINGS.BLOCK_HIGHT, *texture);
		sprite.setPosition(blockPosition.x, blockPosition.y);
		sprite.setColor(sf::Color::Blue);
		type = ObjectType::Simple;
	}

	void Block::Draw(sf::RenderWindow& window)
	{
		if (hitCount > 0) {
			window.draw(sprite);
		}
	}

	void Block::Init()
	{

	}

	void Block::Update(float timeDelta)
	{

	}

	int Block::GetHitCount()
	{
		return hitCount;
	}

	void Block::SetHitCount(const int count)
	{
		hitCount = count;
	}

	void Block::OnHit()
	{
		hitCount -= 1;
	}

	bool Block::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		sf::Vector2f blockPos = sprite.getPosition();
		auto ball = std::dynamic_pointer_cast<Ball>(collidable);
		sf::Vector2f ballPos = ball->GetPosition();
		if (fabs(ballPos.x - blockPos.x) <= (SETTINGS.BLOCK_WIDTH / 2.f) + (SETTINGS.BALL_SIZE / 2.f) &&
			fabs(ballPos.y - blockPos.y) <= (SETTINGS.BLOCK_HIGHT / 2.f) + (SETTINGS.BALL_SIZE / 2.f))
		{
			return true;
		}
		return false;
	}
}
