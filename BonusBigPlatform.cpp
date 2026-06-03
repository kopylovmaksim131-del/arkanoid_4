#include "BonusBigPlatform.h"

namespace ArkanoidGame
{
	BonusBigPlatform::BonusBigPlatform()
	{
		bonusType = BonusType::BigPlatform;
		effect = std::make_unique<SizeEffect>();
		sprite.setColor(sf::Color::Yellow);
	}

	void BonusBigPlatform::ApplyEffect(Platform& platform, Ball& ball)
	{
		effect->Apply(platform, ball);
	}

	void BonusBigPlatform::OnHit()
	{
	}
}