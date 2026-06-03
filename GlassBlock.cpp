#include "GlassBlock.h"
#include "Ball.h"

namespace ArkanoidGame
{
	GlassBlock::GlassBlock(const sf::Vector2f& blockPosition) : Block(blockPosition)
	{
		sprite.setColor(sf::Color::Cyan);
		type = ObjectType::Glass;
	}

	bool GlassBlock::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		sf::Vector2f blockPos = sprite.getPosition();
		auto ball = std::dynamic_pointer_cast<Ball>(collidable);
		sf::Vector2f ballPos = ball->GetPosition();
		if (fabs(ballPos.x - blockPos.x) <= (SETTINGS.BLOCK_WIDTH / 2.f) + (SETTINGS.BALL_SIZE / 2.f) &&
			fabs(ballPos.y - blockPos.y) <= (SETTINGS.BLOCK_HIGHT / 2.f) + (SETTINGS.BALL_SIZE / 2.f))
		{
			ball->SetCollisionParam(false, 0.f, true);
			return true;
		}
		return false;
	}
}
