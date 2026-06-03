#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <assert.h>
#include <array>
#include "GameSettings.h"
#include "Sprite.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	class DecoratorBonus : public GameObject
	{
	protected:
		std::shared_ptr<GameObject> gameObject;
	public:
		DecoratorBonus(std::shared_ptr<GameObject> obj) : gameObject(std::move(obj)) {}

		void Init() override {
			if (gameObject) gameObject->Init();
		}

		void Update(float deltaTime) override {
			if (gameObject) gameObject->Update(deltaTime);
		}

		void Draw(sf::RenderWindow& window) override {
			if (gameObject) gameObject->Draw(window);
		}
	};
}