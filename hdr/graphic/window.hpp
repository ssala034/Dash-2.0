#pragma once 

#include "../gameEngine.hpp"
#include "../logic/player.hpp"


namespace gameEngine {

	namespace window {
		const float xDimension = 800;
		const float yDimension = 800;
		const float groundLvl = yDimension / 2 + 175.0f;

		void createWindow();
		bool isFullScreen(const sf::RenderWindow& window);
		void setUpBackground(sf::Texture& backgroundTexture, std::vector<sf::Sprite>& backgroundSprites);
		void updateBackground(std::vector<sf::Sprite>& sprites, const sf::View& view, const gameEngine::Player& player);

		std::vector<std::array<float, 3>> loadObjectsFromCSV(const std::string& filename);
		bool isObjectInView(const gameEngine::Player& player, gameEngine::Objects& obj);
	}
}



