#include "BonusSlowBallSpeed.h"

namespace ArkanoidGame
{
	BonusSlowBallSpeed::BonusSlowBallSpeed()
	{
		bonusType = BonusType::SlowBall;
		effect = std::make_unique<SpeedEffect>();
		sprite.setColor(sf::Color::Blue);
	}

	void BonusSlowBallSpeed::ApplyEffect(Platform& platform, Ball& ball)
	{
		effect->Apply(platform, ball);
	}

	void BonusSlowBallSpeed::OnHit()
	{
	}
}