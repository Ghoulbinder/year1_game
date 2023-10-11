#include <SFML/Graphics.hpp> // Include the SFML graphics library.
#include <iostream>
#include <sstream>
#include <vector>
#include "entity.h"  // Include the Entity class header
#include "player.h"  // Include the Player class header
#include "ghost.h"   // Include the Ghost class header

using namespace std;
using namespace sf;





void load() {


}



void Update(RenderWindow& window) {


}


int main() 
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man"); // Create a window with a size of 800x600 pixels and a title "SFML Window".
    
    // Create entities
    Player player;

    player.setPosition(sf::Vector2f(400.f, 300.f)); 
    Ghost ghost1, ghost2, ghost3, ghost4;
    
    ghost1.setPosition(sf::Vector2f(200.f, 150.f));
    ghost2.setPosition(sf::Vector2f(200.f, 450.f));
    ghost3.setPosition(sf::Vector2f(600.f, 150.f));
    ghost4.setPosition(sf::Vector2f(600.f, 450.f));

    // Create a vector to hold Entity pointers
    std::vector<Entity*> entities;

    // Add the entities to the vector
    entities.push_back(&player);
    entities.push_back(&ghost1);
    entities.push_back(&ghost2);
    entities.push_back(&ghost3);
    entities.push_back(&ghost4);




    while (window.isOpen()) { // Start a game loop that continues as long as the window is open.
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Close the window if the close button is clicked.
            }
        }

        static Clock clock;
        // Update player
        float dt = clock.restart().asSeconds();
      
        // Update entities
        for (auto& entity : entities) {
            entity->Update(dt);
        }

        window.clear(); // Clear the window.

        
        // Render entities
        for (const auto& entity : entities) {
            entity->Render(window);
           
            
            window.display(); // Display the contents of the window.
        }
    }

    return 0; // Return 0 to indicate successful execution.
}
