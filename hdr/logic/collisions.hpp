#pragma once
#include "../gameEngine.hpp"
#include "player.hpp"
#include "objects.hpp"

namespace gameEngine {

	bool checkCollision(gameEngine::Player& player, const gameEngine::Objects& object);

	bool checkCollisionFromTop(gameEngine::Player& player, const gameEngine::Objects& object);


}