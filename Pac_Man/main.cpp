#include <SFML/Graphics.hpp> // Include the SFML graphics library.
#include "player.h"
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;





void load() {


}



void Update(RenderWindow& window) {


}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window"); // Create a window with a size of 800x600 pixels and a title "SFML Window".
    
    //player with smart pointer
    unique_ptr<Player> player = make_unique<Player>();


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
        player->Update(dt);

        window.clear(); // Clear the window.

        player->Render(window);
        // Draw your graphics here (e.g., shapes, textures, etc.).

        window.display(); // Display the contents of the window.
    }

    return 0; // Return 0 to indicate successful execution.
}
