#include "DecoratorUpBallSpeedBonus.h"

namespace ArkanoidGame
{
	void DecoratorUpBallSpeedBonus::Update(float deltaTime)
	{
		{
			auto ball = dynamic_cast<Ball*>(gameObject.get());
			gameObject->Update(deltaTime * speedMultiplier);
		}
	}
}
