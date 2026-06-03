#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameObject.h"

namespace ArkanoidGame
{
	class ScoreStrategy
	{
	public:
		virtual int Calculate(ObjectType type) = 0;
		virtual ~ScoreStrategy() = default;
	};
}