#include "../../hdr/logic/objects/hpp"
#include "../../hdr/graphic/window.hpp"
#include <iostream>
#include <string>

gameEngine::Objects::Objects() {
	inFrame = false;

}

sf::Sprite gameEngine::Objects::getSprite() const {
	return _objectSprite;
}

sf::Vector2f gameEngine::Objects::getPosition() const {
	return _objectSprite.getPosition();
}
int gameEngine::Objects::getId() const {
	return _id;
}
sf::Texture gameEngine::Objects::getTexture() {
	return _objectTexture;
}
void gameEngine::Objects::setFrame() {
	inFrame = true;
}
bool gameEngine::Objects::getFrame() {
	return inFrame;
}


void gameEngine::Objects::createBlock() {
	if (!_objectTexture.loadFromFile("C:/Users/shuai/OneDrive/Desktop/SFML/assets/greenblock.png")) {
		std::cout << "CANNOT LOAD IMAGE";
	}
	else {
		_loaded = true;
		_id = 1;
		_objectSprite.setTexture(_objectTexture);
	}
}

//really two block on top of each other
void gameEngine::Objects::createWall() {
	if (!_objectTexture.loadFromFile("C:/Users/shuai/OneDrive/Desktop/SFML/assets/smallwall.png")) { // may 
		std::cout << "CANNOT LOAD IMAGE";
	}
	else {
		_loaded = true;
		_id = 2;
		_objectSprite.setTexture(_objectTexture);
	}
}

void gameEngine::Objects::createSpike1() {
	if (!_objectTexture.loadFromFile("C:/Users/shuai/OneDrive/Desktop/SFML/assets/gspikes1.png")) {
		std::cout << "CANNOT LOAD IMAGE";
	}
	else {
		_loaded = true;
		_id = 3;
		_objectSprite.setTexture(_objectTexture);
	}
}


void gameEngine::Objects::createSpike2() {
	if (!_objectTexture.loadFromFile("C:/Users/shuai/OneDrive/Desktop/SFML/assets/gspikes2.png")) {
		std::cout << "CANNOT LOAD IMAGE";
	}
	else {
		_loaded = true;
		_id = 4;
		_objectSprite.setTexture(_objectTexture);
	}
}

void gameEngine::Objects::spawnObj(float x, float y) {

	if (_loaded) {
		if (_id == 1) {
			_objectSprite.setPosition(x, y);
			_objectSprite.setScale(0.35f, 0.35f);

		}
		else if (_id == 2) {
			_objectSprite.setPosition(x, y);
			

		}
		else if (_id == 3) {
			_objectSprite.setPosition(x, y);
			_objectSprite.setScale(0.35f, 0.35f);
		}
		else {
			_objectSprite.setPosition(x, y);
			_objectSprite.setScale(0.2f, 0.35f);

		}

	}

}

void gameEngine::Objects::draw(sf::RenderWindow& window) {
	window.draw(_objectSprite);
}

void gameEngine::Objects::setPosition(float x, float y) {
	_objectSprite.setPosition(x, y);
}

void gameEngine::Objects::createObj(int a, gameEngine::Objects& obj) {

	switch (a) {
	case 1:
		obj.createBlock();
		break;
	case 2:
		obj.createWall();
		break;
	case 3:
		obj.createSpike1();
		break;
	case 4:
		obj.createSpike2();
		break;
	default:
		std::cout << "ERROR";
		break;
	}

}
