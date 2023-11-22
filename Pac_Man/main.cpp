#include <SFML/Graphics.hpp> // Include the SFML graphics library.
#include <iostream>
#include <sstream>
#include <vector>
#include "system_renderer.h"
#include "pacman.h"
#include "entity.h"  // Include the Entity class header
#include "player.h"  // Include the Player class header
#include "ghost.h"   // Include the Ghost class header
#include "EntityManager.h"




using namespace std;
using namespace sf;

// Function declarations
void load();
void update(RenderWindow& window, EntityManager& em, shared_ptr<Scene>& activeScene, Clock& clock);

// Function definitions

void load(RenderWindow& window, EntityManager& em, shared_ptr<Scene>& menuScene, shared_ptr<Scene>& gameScene, shared_ptr<Scene>& activeScene) {
    Renderer::initialise(window);


    // Create entities
    auto player = make_shared<Player>();
    auto ghost1 = make_shared<Ghost>();
    auto ghost2 = make_shared<Ghost>();
    auto ghost3 = make_shared<Ghost>();
    auto ghost4 = make_shared<Ghost>();

    // Set positions for entities
    player->setPosition(Vector2f(400.f, 300.f));
    ghost1->setPosition(Vector2f(200.f, 150.f));
    ghost2->setPosition(Vector2f(200.f, 450.f));
    ghost3->setPosition(Vector2f(600.f, 150.f));
    ghost4->setPosition(Vector2f(600.f, 450.f));

    // Add entities to EntityManager
    em.list.push_back(player);
    em.list.push_back(ghost1);
    em.list.push_back(ghost2);
    em.list.push_back(ghost3);
    em.list.push_back(ghost4);

    // Create and initialize scenes
    MenuScene menu;
    GameScene game;
    menuScene = make_shared<MenuScene>(menu);
    gameScene = make_shared<GameScene>(game);
    activeScene = menuScene; // Start with the menu scene
}


void update(RenderWindow& window, EntityManager& em, shared_ptr<Scene>& activeScene, Clock& clock) {
    float dt = clock.restart().asSeconds(); // Calculate delta time
    cout << "Updating scene..." << endl; // Debug output to ensure this function is being called
    // Check for key presses and update scenes
    if (activeScene == menuScene) {
        cout << "Currently in MenuScene" << endl; // Debug output for current scene
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            cout << "Space key pressed in MenuScene" << endl;
            activeScene = gameScene; // Switch to the GameScene
        }
    }
    else if (activeScene == gameScene) {
        cout << "Currently in GameScene" << endl; // Debug output for current scene
        if (Keyboard::isKeyPressed(Keyboard::Tab)) {
            cout << "Tab key pressed in GameScene" << endl;
            activeScene = menuScene; // Switch to the MenuScene
        }
    }

    activeScene->update(dt); // Update the active scene
    em.update(dt);           // Update EntityManager
}

int main() {
    RenderWindow window(VideoMode(800, 600), "Pac-Man"); // Create a window

   

    //shared_ptr<MenuScene> menuScene;
    //shared_ptr<GameScene> gameScene;
    //shared_ptr<Scene> menuScene;
    // shared_ptr<Scene> gameScene;

    // Declare variables to hold game state
    EntityManager em;
    std::shared_ptr<Scene> menuScene = std::make_shared<MenuScene>();
    std::shared_ptr<Scene> gameScene = std::make_shared<GameScene>();
    shared_ptr<Scene> activeScene; 
    Clock clock;

    load(window, em, menuScene, gameScene, activeScene); // Call load function

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

       

        window.clear(); // Clear the window

        // Render the active scene and entities
        update(window, em, activeScene, clock); // Call update function
        activeScene->render(window);
        em.render(window);

        window.display(); // Display the contents of the window
    }

    return 0;
}

