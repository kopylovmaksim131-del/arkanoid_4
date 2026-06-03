#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "ScoreStrategy.h"

namespace ArkanoidGame
{
	class SimpleScoreStrategy : ScoreStrategy
	{
	public:
		int Calculate(ObjectType type) override
		{
			switch (type) {
			case ObjectType::Simple:
				return 10;
			case ObjectType::Glass:
				return 5;
			case ObjectType::ThreeHit:
				return 20;
			}
		}
	};
}