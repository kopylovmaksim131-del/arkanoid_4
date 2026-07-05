#include "Platform.h"
#include "Ball.h"

namespace ArkanoidGame
{
	sf::Texture* Platform::texture = nullptr;
	
	void Platform::LoadTexture()
	{
		texture = new sf::Texture();
		assert(texture->loadFromFile(SETTINGS.TEXTURES_PATH + "Platform.png"));
	}

	void Platform::Init()
	{
		InitSprite(sprite, SETTINGS.PLATFORM_WIDTH, SETTINGS.PLATFORM_HIGHT, *texture);
		sprite.setPosition(pos.x, pos.y);
		speed = SETTINGS.INITIAL_SPEED;
		type = ObjectType::Platform;
	}

	void Platform::Update(float timeDelta)
	{
		float shift = speed * speedMultiplier * timeDelta;
		const sf::Vector2f newDirection = Platform::GetPlatformDirectionVector(direction) * shift / SETTINGS.PLATFORM_WIDTH;
		sprite.setPosition(sprite.getPosition() + newDirection);
	}

	void Platform::SetDirection(PlatformDirection dir)
	{
		direction = dir;
	}

	void Platform::SetSizeMultiplier(float multiplier, float duration)
	{
		sizeMultiplier = multiplier;
		sizeMultiplierDuration = duration;
		if (!sizeEffectSet)
		{
			SetNewScale();
			sizeEffectSet = true;
		}
	}

	void Platform::SetSpeedMultiplier(float multiplier, float duration)
	{
		speedMultiplier = multiplier;
		speedMultiplierDuration = duration;
	}

	void Platform::SetNewScale()
	{
		sprite.setScale(sprite.getScale().x * sizeMultiplier, sprite.getScale().y);
	}

	PlatformSaveData Platform::GetSaveData()
	{
		PlatformSaveData saveData;
		saveData.position = sprite.getPosition();
		saveData.speedMultiplier = speedMultiplier;
		saveData.speedMultiplierTimer = speedMultiplierTimer;
		saveData.speedMultiplierDuration = speedMultiplierDuration;

		saveData.sizeMultiplier = sizeMultiplier;
		saveData.sizeMultiplierTimer = sizeMultiplierTimer;
		saveData.sizeMultiplierDuration = sizeMultiplierDuration;
		saveData.sizeEffectSet = sizeEffectSet;
		return saveData;
	}

	void  Platform::LoadData(const PlatformSaveData saveData)
	{
		sprite.setPosition(saveData.position);
		speedMultiplier = saveData.speedMultiplier;
		speedMultiplierTimer = saveData.speedMultiplierTimer;
		speedMultiplierDuration = saveData.speedMultiplierDuration;

		sizeMultiplier = saveData.sizeMultiplier;
		sizeMultiplierTimer = saveData.sizeMultiplierTimer;
		sizeMultiplierDuration = saveData.sizeMultiplierDuration;
		sizeEffectSet = saveData.sizeEffectSet;
	}

	sf::Vector2f Platform::GetPlatformDirectionVector(PlatformDirection direction)
	{
		sf::Vector2f result;

		switch (direction)
		{
		case PlatformDirection::Right:
		{
			result = { SETTINGS.PLATFORM_WIDTH, 0.f };
			break;
		}
		case PlatformDirection::Left:
		{
			result = { -SETTINGS.PLATFORM_WIDTH, 0.f };
			break;
		}
		}

		return result;
	}

	void Platform::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	void Platform::OnHit()
	{

	}

	void Platform::UpdateEffect(float timeDelta)
	{
		if (speedMultiplierDuration > 0)
		{
			speedMultiplierTimer += timeDelta;
			if (speedMultiplierTimer >= speedMultiplierDuration)
			{
				speedMultiplier = 1.0f;
				speedMultiplierDuration = 0.0f;
				speedMultiplierTimer = 0.0f;
			}
		}

		if (sizeMultiplierDuration > 0)
		{
			sizeMultiplierTimer += timeDelta;
			if (sizeMultiplierTimer >= sizeMultiplierDuration)
			{
				sizeMultiplier = 0.5f;
				sizeMultiplierDuration = 0.0f;
				sizeMultiplierTimer = 0.0f;
				SetNewScale();
				sizeEffectSet = false;
			}
		}
	}

	bool Platform::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		sf::Vector2f platformPos = sprite.getPosition();
		auto ball = std::dynamic_pointer_cast<Ball>(collidable);
		sf::FloatRect realSize = sprite.getGlobalBounds();
		sf::Vector2f ballPos = ball->GetPosition();
		if (fabs(ballPos.x - platformPos.x) <= (realSize.width / 2.f) + (SETTINGS.BALL_SIZE / 2.f) &&
			fabs(ballPos.y - platformPos.y) <= (realSize.height / 2.f) + (SETTINGS.BALL_SIZE / 2.f))
		{
			ball->SetCollisionParam(true, platformPos.x, false);
			return true;
		}
		return false;
	}
}
