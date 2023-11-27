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
sf::Texture bulletTexture; // Declare a texture for the bullet
sf::Sprite invader;
Mage* playerMage = nullptr; // Initialize the static member
std::vector<Bullet*> bullets;
PauseMenu pauseMenu;

enum class GameState {
    Playing,
    Paused
};

// Function to initialize the bullet pool
void InitializeBulletPool() {
    Bullet::Init();
}


void Load() {
    if (!spritesheet.loadFromFile("C:/Users/romeo/year1_game/res/img/mage.png")) {
        std::cerr << "Failed to load spritesheet." << std::endl;
        // Handle the error, e.g., exit the program
    }
    // Load the texture for the bullet
    if (!bulletTexture.loadFromFile("C:/Users/romeo/year1_game/res/img/Fireball-1.png")) {
        std::cerr << "Failed to load bullet texture." << std::endl;
        // Handle the error, e.g., exit the program
    }
   
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 900), "Wizards of the Abyss");
    Load();

    // Initialize the bullet pool here
    //InitializeBulletPool();

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
    if (startPos.x < 0 || startPos.y < 0) {
        std::cerr << "Start position not found in the level." << std::endl;
        return 1;
    }

    //create a Mage instance
    Mage myMage(sf::IntRect(0, 0, 35, 37), startPos);


    // Load the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/romeo/year1_game/res/img/2nd_map.png")) {
        std::cerr << "Failed to load background image." << std::endl;
        return 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        myMage.FireBullet(false); // Assuming false means it's a player bullet
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

        //if (gameState == GameState::Paused) {
        //    sf::Sprite PauseSprite(pauseMenuBackgroundTexture);
        //    window.draw(PauseSprite);
        //}

        if (gameState == GameState::Playing) {
            // Place all update logic here
            myMage.Update(dt);
            Bullet::Update(dt);

            // Check for spacebar key press and fire a bullet from the Mage
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!spacebarPressed) {
                    myMage.FireBullet(false);
                }
                spacebarPressed = true;
            }
            else {
                spacebarPressed = false;
            }

            // Draw gameplay elements
            window.draw(backgroundSprite);
            LevelSystem::Render(window);
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
