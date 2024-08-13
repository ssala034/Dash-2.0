#include "../../hdr/logic/player.hpp"
#include "iostream"
#include "../../hdr/graphic/window.hpp"
#include <thread>
#include <chrono>


gameEngine::Player::Player() {

	if (!_playerTexture.loadFromFile("C:/Users/shuai/OneDrive/Desktop/SFML/assets/block.png")) {
		// Error handling if the image cannot be loaded
		std::cout << "CANNOT LOAD IMAGE";
	}
	else {
		_playerSprite.setTexture(_playerTexture);
		_playerPosition.x = (gameEngine::window::xDimension) / 2 - 100.0f;
		_playerPosition.y = gameEngine::window::groundLvl;
		xVelocity = 0.5f;
		yVelocity = 0.0f;
		_rotation = 0;
		_jump = true;
		_alive = false;
	}

}

void gameEngine::Player::spawn() {
	_playerSprite.setPosition(_playerPosition);
	_alive = true;

}
sf::Vector2f gameEngine::Player::getVelocity() const {
	sf::Vector2f velocity = sf::Vector2f(xVelocity, yVelocity);
	return velocity;
}

sf::Texture gameEngine::Player::getTexture() {
	return this->_playerTexture;
}

void gameEngine::Player::draw(sf::RenderWindow& window) {
	window.draw(_playerSprite);

}

sf::Vector2f gameEngine::Player::getPosition() const {
	return _playerSprite.getPosition();
}
void gameEngine::Player::setPosition(float x, float y) {
	sf::Vector2f newPos = sf::Vector2f(x, y);

	_playerPosition = newPos;
	_playerSprite.setPosition(_playerPosition);
}

sf::Sprite gameEngine::Player::getSprite() const {
	return _playerSprite;
}

void gameEngine::Player::setJump(bool newJump) {
	_jump = newJump;
}

void gameEngine::Player::move() {
	_playerPosition.x += xVelocity;
	_playerSprite.setPosition(_playerPosition);
}

void gameEngine::Player::update(float delta, gameEngine::Objects& object) {
	const float gravity = 2.0f; // Adjust this value as needed 

	// below ground or moving up 
	if (_playerPosition.y < gameEngine::window::groundLvl || yVelocity < 0) { // If in air or below somehow change so if ontop is allowed
		yVelocity += gravity * delta; // Apply gravity
		_playerPosition.y += yVelocity;

		if (onTopOfObject(object)) {
			//player ontop of object , set position to its top, LOOK at logic of claminping here
			if (object.getId() == 1) {
				_playerPosition.y = 490.0f;
				yVelocity = 0.0f;
				_jump = true;
			}
			else {
				_playerPosition.y = 460.0f;           // Clamp position at object level, relative to bottom sprite pos
				yVelocity = 0.0f; // Stop vertical movement
				_jump = true; // Allow jumping again
			}

		}
		else if (_playerPosition.y > gameEngine::window::groundLvl) {
			// Player is falling below the ground level
			_playerPosition.y = gameEngine::window::groundLvl; // Clamp position at ground level
			yVelocity = 0.0f;
			_jump = true;
		}
	}

	_playerSprite.setPosition(_playerPosition);

}

//only for block and wall
bool gameEngine::Player::onTopOfObject(const gameEngine::Objects& object) {
	if (object.getId() == 4 || object.getId() == 3) {
		return false;
	}
	const float tolerance = 3.0f; // Tolerance for collision detection

	sf::FloatRect playerBounds = getSprite().getGlobalBounds();
	sf::FloatRect objectBounds = object.getSprite().getGlobalBounds();

	// Check horizontal alignment (player must be within tolerance horizontally)
	bool isAlignedHorizontally = (playerBounds.left + playerBounds.width > objectBounds.left) &&
		(playerBounds.left < objectBounds.left + objectBounds.width);

	// Check if the player is just above the object within tolerance
	bool isOnTop = (playerBounds.top + playerBounds.height <= objectBounds.top + tolerance);

	return isAlignedHorizontally && isOnTop;

}


void gameEngine::Player::reset() {
	_playerPosition.x = (gameEngine::window::xDimension) / 2;
	_playerPosition.y = gameEngine::window::groundLvl;
	_playerSprite.setPosition(_playerPosition);
	_jump = true;
	_alive - true;

}


void gameEngine::Player::jump(float delta) {
	float gravity = 2.0f;
	float jumpHeight = 0.75f; // Higher value results in higher jumps

	if (_jump) {
		yVelocity = -sqrtf(0.5f * gravity * jumpHeight); // Calculate initial jump velocity
		_jump = false;
	}

}

bool gameEngine::Player::canJump() const {
	return _jump;

}

void gameEngine::Player::setLife(bool life) {
	_alive = life;
}

bool gameEngine::Player::isAlive() {
	return _alive;
}





void gameEngine::Player::resizeSprite(sf::RenderWindow& window) {
	sf::Vector2u windowSize = window.getSize();

	sf::Vector2u textureSize = _playerTexture.getSize();
	float scale = 0.0f;
	float desiredWidth = 0;
	float desiredHeight = 0;

	if (gameEngine::window::isFullScreen(window)) {
		scale = 0.02f;
		std::cout << "BIG";
		desiredWidth = (windowSize.x * scale);
		desiredHeight = (desiredWidth / textureSize.x) * textureSize.y * 2.0f; // Maintain aspect ratio

	}
	else {
		scale = 0.1f;
		std::cout << "Small";
		desiredWidth = (windowSize.x * scale); 
		desiredHeight = (desiredWidth / textureSize.x) * textureSize.y; // Maintain aspect ratio
	}

	float scaleX = static_cast<float>(desiredWidth / textureSize.x);
	float scaleY = static_cast<float>(desiredHeight / textureSize.y);

	// Apply the scaling to the sprite
	_playerSprite.setScale(scaleX, scaleY);
}


