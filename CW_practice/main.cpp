#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Game.h"
#include "Bullet.h"
#include "LevelSystem.h"
#include "PauseMenu.h"


using namespace std;
using namespace sf;

sf::Texture spritesheet;
sf::Texture mageSpritesheet; // Texture for the Mage
sf::Texture slimeSpritesheet; // Texture for the Slime
sf::Texture bulletTexture; // Texture for the bullet

Mage* playerMage = nullptr; // Initialize the static member
std::vector<Bullet*> bullets;
PauseMenu pauseMenu;

enum class GameState {
    Playing,
    Paused
};

// Function to initialize the bullet pool
void InitializeBulletPool() {
    std::cout << "Initializing Bullet Pool..." << std::endl; // Debug statement
    Bullet::Init();
    std::cout << "Bullet Pool Initialized." << std::endl; // Debug statement
}




void Load() {
    // Load the Mage spritesheet
    if (!mageSpritesheet.loadFromFile("C:/Users/romeo/year1_game/res/img/mage.png")) {
        std::cerr << "Failed to load Mage spritesheet." << std::endl;
    }
    else {
        std::cout << "Mage spritesheet loaded successfully." << std::endl;
    }

    // Load the Slime spritesheet
    if (!slimeSpritesheet.loadFromFile("C:/Users/romeo/year1_game/res/img/slime_brown.png")) {
        std::cerr << "Failed to load Slime spritesheet." << std::endl;
    }
    else {
        std::cout << "Slime spritesheet loaded successfully." << std::endl;
    }

    // Load the bullet texture using bulletTexture
    if (!bulletTexture.loadFromFile("C:/Users/romeo/year1_game/res/img/Fireball-1.png")) {
        std::cerr << "Failed to load bullet texture." << std::endl;
    }
    else {
        std::cout << "Bullet texture loaded successfully." << std::endl;
    }
}



int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 900), "Wizards of the Abyss");
    Load();

    // Initialize the bullet pool here
   InitializeBulletPool();

     // Initialize the game state to Playing
    GameState gameState = GameState::Playing;


    // Load the background image for the pause menu
    sf::Texture pauseMenuBackgroundTexture;
    if (!pauseMenuBackgroundTexture.loadFromFile("C:/Users/romeo/year1_game/res/img/book_pages.png")) {
        std::cerr << "Failed to load pause menu background image." << std::endl;
        return 1;
    }

    // Create an instance of the PauseMenu and pass the background texture
    PauseMenu pauseMenu(pauseMenuBackgroundTexture);


    LevelSystem::loadLevelFile("C:\\Users\\romeo\\year1_game\\res\\levels\\level_2.txt", 35.f); // You'll need to provide the correct path

    // Get the start position from the level system
    sf::Vector2f startPos = LevelSystem::getStartTilePosition();
    sf::Vector2f enemyPos = LevelSystem::getEnemyTilePosition();
    if (startPos.x < 0 || startPos.y < 0) {
        std::cerr << "Start position not found in the level." << std::endl;
        return 1;
    }
    // Create an instance of the Slime class and set its texture using the loaded spritesheet
    Slime slime(sf::IntRect(0, 0, 49, 62), enemyPos, slimeSpritesheet);
    slime.setTexture(slimeSpritesheet); // Set the texture for the Slime

    // Create an instance of the Mage class and set its texture using the loaded spritesheet
    Mage myMage(sf::IntRect(0, 0, 35, 37), startPos, mageSpritesheet);
    myMage.setTexture(mageSpritesheet); // Set the texture for the Mage


    // Load the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/romeo/year1_game/res/img/2nd_map.png")) {
        std::cerr << "Failed to load background image." << std::endl;
        return 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f direction = mousePos - myMage.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // Normalize the direction

        myMage.FireBullet(false, direction); // Now with the direction argument
    }


    // Declare an sf::Clock object
    sf::Clock clock;


    sf::Sprite backgroundSprite(backgroundTexture);

    // Create a sprite for the pause menu 
    sf::Sprite PauseSprite(pauseMenuBackgroundTexture);


    // Variable to track whether the spacebar was previously pressed
    bool spacebarPressed = false;
   
    // Variable to track whether the 'P' key was pressed in the previous frame
    static bool prevPKeyPressed = false;

    while (window.isOpen()) {
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        float dt = clock.restart().asSeconds();



        bool pKeyCurrentlyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
        if (pKeyCurrentlyPressed && !prevPKeyPressed) {
            gameState = (gameState == GameState::Playing) ? GameState::Paused : GameState::Playing;
            std::cout << "Game state changed to: " << ((gameState == GameState::Paused) ? "Paused" : "Playing") << std::endl;
        }
        prevPKeyPressed = pKeyCurrentlyPressed;


        // Update the previous key state
        prevPKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::P);

        window.clear();

        //gamestates
        if (gameState == GameState::Playing) {
            // Place all update logic here
            myMage.Update(dt);
            Bullet::Update(dt);
            slime.Update(dt); 
           
            // Get the current view from the window
            const sf::View& currentView = window.getView();

            // Get mouse position in screen coordinates
            sf::Vector2i screenMousePos = sf::Mouse::getPosition(window);

            // Convert screen coordinates to world coordinates
            sf::Vector2f worldMousePos = window.mapPixelToCoords(screenMousePos, currentView);

            bool isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            if (isSpacePressed && !spacebarPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2f direction = mousePos - myMage.getPosition();
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                direction /= length; // Normalize the direction

                myMage.FireBullet(false, direction); // Pass the direction to the FireBullet method

                spacebarPressed = true;
            }
            else if (!isSpacePressed) {
                spacebarPressed = false;
            }
            spacebarPressed = isSpacePressed; // Update the state of spacebarPressed


            // Draw gameplay elements
            window.draw(backgroundSprite);
            LevelSystem::Render(window);
            window.draw(slime);
            window.draw(myMage);
            Bullet::Render(window);

        }
        else if (gameState == GameState::Paused) {
            // Draw the pause menu here 
            window.draw(PauseSprite);
        }

        window.display();
       
    }

    return 0;
}
