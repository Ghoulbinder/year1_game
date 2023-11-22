//pacman.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "scene.h"
#include "system_renderer.h" // Include the header file that defines the Renderer class
#include "pacman.h"

using namespace std;
using namespace sf;

// Define the external variables in pacman.cpp
std::shared_ptr<Scene> gameScene;
std::shared_ptr<Scene> menuScene;
std::shared_ptr<Scene> activeScene;


// void Scene::render() { _ents.render(); }
void Scene::render(sf::RenderWindow& window) {
    for (const auto& entity : _ents.list) {
        entity->Render(window);
    }
};

void MenuScene::update(double dt) {
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        activeScene = gameScene;
    }
    Scene::update(dt);
    text.setString("Almost Pacman");
}

void MenuScene::render(sf::RenderWindow& window) {
    Renderer::queue(&text);
    Scene::render(window);
}

void MenuScene::load() {
    // Load the font
    sf::Font font;
    // Load the font with double backslashes
    if (!font.loadFromFile("C:\\Users\\romeo\\year1_game\\res\\fonts\\Roboto-Black.ttf")) {
        // Handle font loading error
        cout << "Error: Font file not found or failed to load!" << endl;
    }
  
    // Set the font for your text element
    text.setFont(font);

    // Additional text properties (e.g., size, color, position)
    text.setCharacterSize(36);  // Set the character size
    text.setFillColor(sf::Color::White); // Set the text color
    text.setPosition(100.f, 100.f); // Set the text position
}

void GameScene::update(double dt) {
    if (Keyboard::isKeyPressed(Keyboard::Tab)) {
        activeScene = menuScene;
    }
    Scene::update(dt);
    // Additional game-specific update logic for the GameScene
}

void GameScene::render(sf::RenderWindow& window) {
    // Additional game-specific rendering logic for the GameScene
    Scene::render(window);
}

void GameScene::load() {
    // Load game-specific content for the GameScene
     // Create and add the player entity
    auto player = std::make_shared<Player>();
    player->setPosition(sf::Vector2f(400.f, 300.f)); // Set the player's position
    _ents.list.push_back(player);

    // Create and add the ghosts
    for (int i = 0; i < 4; i++) {
        auto ghost = std::make_shared<Ghost>();
        // Set the position for each ghost based on your game logic
        // You can adjust these positions as needed
        if (i == 0) {
            ghost->setPosition(sf::Vector2f(200.f, 150.f));
        }
        else if (i == 1) {
            ghost->setPosition(sf::Vector2f(200.f, 450.f));
        }
        else if (i == 2) {
            ghost->setPosition(sf::Vector2f(600.f, 150.f));
        }
        else if (i == 3) {
            ghost->setPosition(sf::Vector2f(600.f, 450.f));
        }
        _ents.list.push_back(ghost);
    }
};

