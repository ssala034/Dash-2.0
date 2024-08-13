#pragma once
#include "../gameEngine.hpp"

namespace gameEngine {
	class Objects { // for a general object
	public:
		Objects();
		void createBlock();
		void createSpike1();
		void createSpike2();
		void createWall();
		void spawnObj(float x, float y);
		void draw(sf::RenderWindow& window);
		sf::Sprite getSprite() const;
		sf::Vector2f getPosition() const;
		sf::Texture getTexture();
		void setPosition(float x, float y);
		int getId() const;
		void setFrame();
		bool getFrame();
		void createObj(int a, gameEngine::Objects& obj);



	private:
		sf::Vector2f _objectPos;
		sf::Texture _objectTexture;
		sf::Sprite _objectSprite;
		bool _loaded = false;
		int _id;
		bool inFrame;
	};
}