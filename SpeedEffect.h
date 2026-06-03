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
    class SpeedEffect : public BonusEffect 
    {
        void Apply(Platform& platform, Ball& ball) override 
        {
            ball.SetSpeedMultiplier(0.5f, 5.f);
        }
    };
}