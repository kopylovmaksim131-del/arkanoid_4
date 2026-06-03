#pragma once
#include <SFML/Graphics.hpp>
//#include "LevelLoader.h"

namespace ArkanoidGame
{
	enum class ObjectType
	{
		Simple,
		ThreeHit,
		Glass,
		Ball,
		Platform,
		Bonus
	};

	class GameObject
	{
	public:
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Draw(sf::RenderWindow& window) = 0;

		const sf::Vector2f& GetPosition() { return sprite.getPosition(); };
		const void SetPosition(const sf::Vector2f pos) { sprite.setPosition(pos); };
		const sf::FloatRect& GetRect() const { return sprite.getGlobalBounds(); };
		const ObjectType GetType() const { return type; };

	protected:
		sf::Sprite sprite;
		ObjectType type;
	};
}