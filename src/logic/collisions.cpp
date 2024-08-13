#include "../../hdr/logic/collisions.hpp"



bool gameEngine::checkCollision(gameEngine::Player& player, const gameEngine::Objects& object) {
    if (player.getSprite().getGlobalBounds().intersects(object.getSprite().getGlobalBounds())) {
        player.setLife(false);
        return true;
    }
    else {
        return false;
    }

}


//return true if collides from top
bool gameEngine::checkCollisionFromTop(gameEngine::Player& player, const gameEngine::Objects& object) {
    sf::Sprite pSprite = player.getSprite();
    sf::Sprite oSprite = object.getSprite();

    sf::FloatRect bounds1 = pSprite.getGlobalBounds(); // player
    sf::FloatRect bounds2 = oSprite.getGlobalBounds(); // object

    bool onTop = false; // assume no collision from top

    // Check if sprites are intersecting
    if (bounds1.intersects(bounds2)) { // maybe add that falling down??????

        // Check if the collision is from above
        // sprite1's bottom must be above sprite2's top

        if (pSprite.getPosition().y + bounds1.height <= oSprite.getPosition().y + 5) {
            onTop = true; // Collision from the top
        }
    }
   
    if (!onTop)
        player.setLife(false);

    return onTop;
}
