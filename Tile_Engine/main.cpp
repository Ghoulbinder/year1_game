#include <SFML/Graphics.hpp> // Include the SFML Graphics module for graphics programming.
#include "LevelSystem.h"     // Include the header for the level system, presumably for level management.
#include "player.h"          // Include the header for the player character.
#include "Entity.h"          // Include the header for entities in the game (like enemies, NPCs, etc.).
#include <iostream>          // Include the standard input/output stream library for console I/O.
#include <sstream>           // Include the string stream library, often used for string manipulation.
#include <fstream>
#include <string>
using namespace std;         // Use the standard namespace to avoid prefixing std:: on standard library types/functions.
using namespace sf;          // Use the sf (SFML) namespace to avoid prefixing sf:: on SFML types/functions.

void load() {
    string levelPath = "C:\\Users\\romeo\\year1_game\\res\\levels\\maze.txt"; // Specify the correct path
    float tileSize = 100.f; // You need to define the tileSize you want to use here

        ls::loadLevelFile("res/levels/maze.txt");

    // Print the level to the console
    for (size_t y = 0; y < ls::getHeight(); ++y) {
        for (size_t x = 0; x < ls::getWidth(); ++x) {
            cout << ls::getTile({ x, y });
        }
        cout << endl;
    }
}

void Render(RenderWindow& window) {
    ls::Render(window);
    
}

int main() {
  


    sf::RenderWindow window(sf::VideoMode(811, 408), "SFML Window"); // Create a window with a size of 800x600 pixels and the title "SFML Window".

    unique_ptr<Player> player = make_unique<Player>();    // Create a unique_ptr to a Player object using make_unique.

    // Initialize the level system
    string path = "C:\\Users\\romeo\\year1_game\\res\\levels\\maze_2.txt";
    ifstream file(path);

    if (!file) {
        // If the file couldn't be opened (doesn't exist or isn't readable)
        cerr << "Unable to open file: " << path << endl;
        return 1; // Return a non-zero value to indicate failure
    }
    else {
        // The file is successfully opened, now we can load the level
        LevelSystem::loadLevelFile(path);
        // Assuming loadLevelFile can take ifstream as an argument
    }

    // Close the file as it's no longer needed after loading the level
    file.close();


    while (window.isOpen()) {                             // Start a game loop that continues as long as the window is open.
        try {
            sf::Event event;
            while (window.pollEvent(event)) {             // Poll for and process events.
                if (event.type == sf::Event::Closed) {
                    window.close();                       // Close the window if the close event is detected.
                }

            }

            static Clock clock;                           // Declare a static clock to measure time intervals.
            float dt = clock.restart().asSeconds();       // Restart the clock and get the elapsed time in seconds.
            player->Update(dt);                           // Update the player with the elapsed time.

            window.clear();                               // Clear the window to prepare for drawing a new frame.

            LevelSystem::Render(window);                  // Render the level.

            player->Render(window);                       // Render the player.

            window.display();                             // Display the rendered frame.
        }
             catch (const std::out_of_range& e) {
            std::cerr << "Exception caught in game loop: " << e.what() << '\n'; // If an exception is caught, log the message.
            // Here you can handle exceptions that may occur during game updates or rendering.
           }

    }
    return 0; // Return 0 to indicate successful execution of the program.
}
