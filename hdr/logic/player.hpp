#pragma once
#include "../gameEngine.hpp"
#include "objects.hpp"


namespace gameEngine {
	class Player {
		const float _x = 0.0f;
		const float _y = 0.0f;

	public:
		Player();
		void spawn();
		sf::Texture getTexture();
		void draw(sf::RenderWindow& window);
		void resizeSprite(sf::RenderWindow& window);
		sf::Vector2f getPosition() const;
		void setPosition(float x, float y);
		sf::Sprite getSprite() const;
		sf::Vector2f getVelocity() const;
		void move();
		void jump(float delta);
		bool canJump() const;
		void setJump(bool newJump);
		void update(float delta, gameEngine::Objects& object);
		void reset();
		bool onTopOfObject(const gameEngine::Objects& object);
		bool isAlive();
		void setLife(bool life);



	private:
		sf::Vector2f _playerPosition;
		sf::Texture _playerTexture;
		sf::Sprite _playerSprite;
		float xVelocity;
		float yVelocity;
		int _rotation;
		bool _jump;
		bool _alive;


		/*sf::Image _icon;*/

	};
}