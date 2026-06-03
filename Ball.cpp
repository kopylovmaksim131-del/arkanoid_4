#include "Ball.h"
#include "Block.h"

namespace ArkanoidGame
{
	sf::Texture* Ball::texture = nullptr;

	void Ball::LoadTexture()
	{
		texture = new sf::Texture();
		assert(texture->loadFromFile(SETTINGS.TEXTURES_PATH + "Ball.png"));
	}

	void Ball::Init()
	{
		InitSprite(sprite, SETTINGS.BALL_SIZE, SETTINGS.BALL_SIZE, *texture);
		sprite.setPosition(pos.x, pos.y);
		speed = SETTINGS.INITIAL_SPEED;
		type = ObjectType::Ball;
	}

	void Ball::Update(float timeDelta)
	{
		CheckBonusEffect(timeDelta);

		float shift = speed * speedMultiplier * timeDelta;
		const sf::Vector2f newDirection = speedVector * shift / SETTINGS.BALL_SIZE;
		sprite.setPosition(sprite.getPosition() + newDirection);
	}

	void Ball::SetDirection(PlatformDirection dir)
	{
		direction = dir;
	}

	sf::Vector2f Ball::GetBallDirectionVector(PlatformDirection direction)
	{
		sf::Vector2f result;

		switch (direction)
		{
		case PlatformDirection::Right:
		{
			result = { SETTINGS.BALL_SIZE, 0.f };
			break;
		}
		case PlatformDirection::Left:
		{
			result = { -SETTINGS.BALL_SIZE, 0.f };
			break;
		}
		}

		return result;
	}

	sf::Vector2f Ball::GetSpeedVector()
	{
		return speedVector;
	}

	void Ball::SetSpeedVector(const sf::Vector2f& v)
	{
		speedVector.x = v.x;
		speedVector.y = v.y;
	}

	void Ball::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	void Ball::SetCollisionParam(bool isPlatform, float platformPos, bool isGlassBlock)
	{
		isCollisionWithPlatform = isPlatform;
		platformPosX = platformPos;
		isCollisionWithGlassBlock = isGlassBlock;
	}

	void Ball::SetSpeedMultiplier(float multiplier, float duration)
	{
		speedMultiplier = multiplier;
		speedMultiplierDuration = duration;
	}

	BallSaveData Ball::GetSaveData()
	{
		BallSaveData saveData;
		saveData.position = sprite.getPosition();
		saveData.direction = direction;
		saveData.speedVector = speedVector;
		saveData.speedMultiplier = speedMultiplier;
		saveData.speedMultiplierTimer = speedMultiplierTimer;
		saveData.speedMultiplierDuration = speedMultiplierDuration;
		return saveData;
	}

	void Ball::LoadData(const BallSaveData saveData)
	{
		sprite.setPosition(saveData.position);
		direction = saveData.direction;
		speedVector = saveData.speedVector;
		speedMultiplier = saveData.speedMultiplier;
		speedMultiplierTimer = saveData.speedMultiplierTimer;
		speedMultiplierDuration = saveData.speedMultiplierDuration;
	}

	void Ball::OnHit()
	{
		if (isCollisionWithPlatform)
		{
			sf::Vector2f ballPos = sprite.getPosition();
			SetSpeedVector(sf::Vector2f{ (ballPos.x - platformPosX) * 4.f, -speedVector.y });
			isCollisionWithPlatform = false;
			platformPosX = 0.f;
		}
		else if (isCollisionWithGlassBlock)
		{
			isCollisionWithGlassBlock = false;
		}
		else
		{
			SetSpeedVector(sf::Vector2f{ speedVector.x, -speedVector.y });
		}
	}

	void Ball::CheckBonusEffect(float timeDelta)
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
	}

	bool Ball::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		return false;
	}

}

