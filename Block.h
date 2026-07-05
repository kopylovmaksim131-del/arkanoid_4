#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Collidable.h"

namespace ArkanoidGame
{
	class Block : public GameObject, public Collidable
	{
	protected:
		int hitCount = 1;

	public:
		Block(const sf::Vector2f& blockPosition);

		void Init() override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;

		int GetHitCount();
		void SetHitCount(const int count);

		static sf::Texture* texture;
		static void LoadTexture();

	private:
		void OnHit();
		std::vector<sf::Color> blockColors{ sf::Color::White, sf::Color::Red, sf::Color::Yellow, sf::Color::Blue };
	};
}
