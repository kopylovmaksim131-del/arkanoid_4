#include "BonusFastPlatform.h"

namespace ArkanoidGame
{
	BonusFastPlatform::BonusFastPlatform()
	{
		bonusType = BonusType::FastPlatform;
		effect = std::make_unique<SpeedEffectPlatform>();
		sprite.setColor(sf::Color::Red);
	}

	void BonusFastPlatform::ApplyEffect(Platform& platform, Ball& ball)
	{
		effect->Apply(platform, ball);
	}

	void BonusFastPlatform::OnHit()
	{
	}
}