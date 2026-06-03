#include "Bonus.h"

namespace ArkanoidGame
{
	sf::Texture* Bonus::texture = nullptr;

	void Bonus::Init()
	{
		InitSprite(sprite, SETTINGS.BONUS_SIZE, SETTINGS.BONUS_SIZE, *texture);
		//sprite.setPosition(pos.x, pos.y);
		type = ObjectType::Bonus;
	}

	void Bonus::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	void Bonus::Update(float timeDelta)
	{
		float shift = speed * timeDelta;
		sf::Vector2f direction{ 0.f, SETTINGS.BONUS_SIZE };
		const sf::Vector2f newDirection = direction * shift / SETTINGS.BONUS_SIZE;
		sprite.setPosition(sprite.getPosition() + newDirection);
	}

	bool Bonus::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		sf::Vector2f bonusPos = sprite.getPosition();
		auto platform = std::dynamic_pointer_cast<Platform>(collidable);
		sf::Vector2f platformPos = platform->GetPosition();
		if (fabs(bonusPos.x - platformPos.x) <= (SETTINGS.PLATFORM_WIDTH / 2.f) + (SETTINGS.BONUS_SIZE / 2.f) &&
			fabs(bonusPos.y - platformPos.y) <= (SETTINGS.PLATFORM_HIGHT / 2.f) + (SETTINGS.BONUS_SIZE / 2.f))
		{
			return true;
		}
		return false;
	}

	void Bonus::LoadTexture()
	{
		texture = new sf::Texture();
		assert(texture->loadFromFile(SETTINGS.TEXTURES_PATH + "Bonus.png"));
	}

	void Bonus::ApplyEffect(Platform& p, Ball& b)
	{
	}
	BonusType Bonus::GetBonusType()
	{
		return bonusType;
	}
}