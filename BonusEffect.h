#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Platform.h"
#include "Collidable.h"

namespace ArkanoidGame
{
    class BonusEffect 
    {
    public:
        virtual void Apply(Platform& platform, Ball& ball) = 0;
        virtual ~BonusEffect() = default;
    };
}