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
#include "BonusEffect.h"

namespace ArkanoidGame
{
    class SizeEffect : public BonusEffect
    {
        void Apply(Platform& platform, Ball& ball) override
        {
            platform.SetSizeMultiplier(2.f, 5.f);
        }
    };
}