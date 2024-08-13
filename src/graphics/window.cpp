#include "./../hdr/graphic/window.hpp"
#include "iostream"
#include "./../hdr/logic/player.hpp"
#include "./../hdr/logic/objects.hpp"
#include "../../hdr/logic/collisions.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include<array>


void gameEngine::window::createWindow() {
    // Create a fullscreen window with the current desktop resolution
    sf::RenderWindow window(sf::VideoMode(gameEngine::window::xDimension, gameEngine::window::yDimension), "AI GeometryDash!");



    // Load a texture (background image)
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/shuai/OneDrive/Desktop/SFML/assets/greenbg2.png")) {  // Change to PNG image
        // Error handling if the image cannot be loaded
        std::cout << "CANNOT LOAD IMAGE";
    }

    std::vector<sf::Sprite> backgroundSprites;

    setUpBackground(backgroundTexture, backgroundSprites);

    std::vector<std::array<float, 3>> positionInfo = gameEngine::window::loadObjectsFromCSV("C:/Users/shuai/OneDrive/Desktop/SFML/assets/dash.csv");

    std::vector<gameEngine::Objects> objectVec;

    gameEngine::Player player;


    player.spawn(); 
    player.resizeSprite(window);

    sf::View view(sf::FloatRect(0, 0, gameEngine::window::xDimension, gameEngine::window::yDimension));
    view.setSize(gameEngine::window::xDimension, gameEngine::window::yDimension);
    view.setCenter(player.getPosition());
    sf::Clock clock;

    // set to inital object



    for (int i = 0; i < positionInfo.size(); i++) {
        gameEngine::Objects tempObj;
        int id = positionInfo[i][2];
        std::cout << id;
        if (id == 1) {
            tempObj.createBlock();
        }
        else if (id == 2) {
            tempObj.createWall();
        }
        else if (id == 3) {
            tempObj.createSpike1();
        }
        else {
            tempObj.createSpike2();
        }

        tempObj.spawnObj(static_cast<float>(positionInfo[i][0]), static_cast<float>(positionInfo[i][1]));
        std::cout << tempObj.getPosition().x << tempObj.getPosition().y << "\n \n";
        objectVec.push_back(tempObj);
    }

   

      // Main loop that continues until the window is closed
    while (window.isOpen()) {
        // Process events
        sf::Time delta = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                // place to handle resizing the window, player, etc

                player.resizeSprite(window);
            }
        }
        gameEngine::Objects currentObj;

        for (auto& obj : objectVec) {
            if (isObjectInView(player, obj)) {
                currentObj = obj;

            }
        }


        player.move();
        view.setCenter(player.getPosition());



        sf::Vector2f pos = player.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.canJump()) {
            player.jump(delta.asSeconds());
        }

        //now for the ones in view, must check for collisions and update player for collisions,

        if (currentObj.getId() == 3 || currentObj.getId() == 4) {
            if (checkCollision(player, currentObj)) {
                player.reset();
                setUpBackground(backgroundTexture, backgroundSprites);
            }
        }
        else {
            if (checkCollisionFromTop(player, currentObj) || checkCollision(player, currentObj)) {
                player.reset();
                setUpBackground(backgroundTexture, backgroundSprites);
            }
        }

        

        player.update(delta.asSeconds(), currentObj); // will change so its a pointer so dynamically pick which object 


        view.setCenter(player.getPosition());



        //don't do reset cuz it will do it each frame !!!!
        updateBackground(backgroundSprites, view, player);

        window.setView(view);

        // Clear the window with a color (optional, background will overwrite this)
        window.clear(sf::Color::Black);

        //drawing array of objects

        // Draw the background
        for (const auto& bg : backgroundSprites) {
            window.draw(bg);
        }

       

        currentObj.draw(window);

        player.draw(window);

        // Display the contents of the window
        window.display();
    }
}

void gameEngine::window::setUpBackground(sf::Texture& backgroundTexture, std::vector<sf::Sprite>& backgroundSprites) {
    // to get the window clipping effect to work, must have multiple bg's


    backgroundSprites.clear(); // must clear so if resets the player sprites are done again

    float initialScale = static_cast<float>(gameEngine::window::yDimension) / backgroundTexture.getSize().y;
    float initialWidth = backgroundTexture.getSize().x * initialScale;

    float scaleX = static_cast<float>(gameEngine::window::xDimension) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(gameEngine::window::yDimension) / backgroundTexture.getSize().y;
    float maxScale = std::max(scaleX, scaleY);  // Ensure no gaps by using the larger scale factor

    float scaledWidth = backgroundTexture.getSize().x * maxScale;
    float scaledHeight = backgroundTexture.getSize().y * maxScale;

    // Calculate how many sprites are needed to cover the screen width
    int numBackgrounds = ceil(gameEngine::window::xDimension / initialWidth) + 1;

    

    for (int i = 0; i < numBackgrounds; i++) {
        sf::Sprite sprite;
        sprite.setTexture(backgroundTexture);

        sprite.setTexture(backgroundTexture);

        // Scale each background sprite to ensure it covers the vertical space completely
        sprite.setScale(maxScale, maxScale);
        sprite.setPosition(static_cast<float>(i * backgroundTexture.getSize().x * maxScale), 0);
        backgroundSprites.push_back(sprite);
    }

}

void gameEngine::window::updateBackground(std::vector<sf::Sprite>& backgroundSprites, const sf::View& view, const gameEngine::Player& player) {

    float viewWidth = view.getSize().x;
    float viewCenterX = view.getCenter().x;

    for (auto& sprite : backgroundSprites) {
        if (sprite.getPosition().x + sprite.getGlobalBounds().width < viewCenterX - viewWidth / 2) {
            sprite.move(sprite.getGlobalBounds().width * backgroundSprites.size(), 0);
        }
    }

}
std::vector<std::array<float, 3>> gameEngine::window::loadObjectsFromCSV(const std::string& filename) {

    std::ifstream file(filename);
    std::vector<std::array<float, 3>> info;

    if (!file.is_open()) {
        std::cout << "Error in opening file" << std::endl;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line); 
        std::string xStr;
        std::array<float, 3> temp;

        int i = 0;
        while (std::getline(ss, xStr, ',')) {
            std::stringstream stemp;
            stemp << xStr;

            int input = 0;
            stemp >> input;
            temp[i] = static_cast<float>(input);
            i++;
            if (i == 3) {
                break;
            }
        }
        info.push_back(temp);
    }

    file.close();
    return info;
}

bool gameEngine::window::isObjectInView(const gameEngine::Player& player, gameEngine::Objects& obj) {
    float playerX = player.getSprite().getGlobalBounds().left;
    float objX = obj.getSprite().getGlobalBounds().left;
    float halfWindowWidth = gameEngine::window::xDimension / 2;

    return objX >= playerX - halfWindowWidth && objX <= playerX + halfWindowWidth;
}


bool gameEngine::window::isFullScreen(const sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    if (windowSize.x > 1000.0f && windowSize.y > 1000.0f) {
        return true;
    }
    else {
        return false;
    }
    /* sf::Vector2u windowSize = window.getSize();
     sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

     bool isFullscreen = (windowSize.x == videoMode.width && windowSize.y == videoMode.height);
     return isFullscreen;*/
}


