#include "../../hdr/graphic/map.hpp"
#include <iostream>




void Map::createMap() {
    // Create a fullscreen window with the current desktop resolution
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

    // Load a texture (background image)
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/shuai/OneDrive/Desktop/GeometryDash 2.0/assets/greenbg2.png")) {  // Change to PNG image
        // Error handling if the image cannot be loaded
        std::cout << "Does not load";
    }


    // Create a sprite from the texture
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Get the window size and the texture size
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();

    // Scale the sprite to fit the window size
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Main loop that continues until the window is closed
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a color (optional, background will overwrite this)
        window.clear(sf::Color::Black);

        // Draw the background
        window.draw(backgroundSprite);

        // Display the contents of the window
        window.display();
    }

}

