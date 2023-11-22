// Ensures the header is only included once during compilation
#pragma once

// Including necessary header files
#include <SFML/Graphics.hpp> // For SFML graphics classes
#include <memory> // For smart pointer utilities
#include <string> // For string class
#include <vector> // For vector container
#include <map> // For map container
#include "maths.h" // For mathematical functions, assuming this is a local header

// Define shorthand notation for easier access to the LevelSystem class
#define ls LevelSystem

// Declaration of the LevelSystem class
class LevelSystem {
public:
    // Enumeration to represent different types of tiles within the level
    enum TILE { EMPTY, START, END, WALL, ENEMY, WAYPOINT };

   // Static function to get the width of the level
   static size_t getWidth() {
       return _width;
   }
  
   // Static function to get the height of the level
   static size_t getHeight() {
       return _height;
   }

    // Load level from file
    static void loadLevelFile(const std::string&, float tileSize = 100.f);
    // Render the level to a window
    static void Render(sf::RenderWindow& window);
    // Get color associated with a tile type
    static sf::Color getColor(TILE t);
    // Set color for a tile type
    static void setColor(TILE t, sf::Color c);
    // Get the tile type at grid coordinates
    static TILE getTile(sf::Vector2ul);
    // Get the screenspace position of a tile
    static sf::Vector2f getTilePosition(sf::Vector2ul);
    // Get the tile type at screenspace position
    static TILE getTileAt(sf::Vector2f);

protected:
    // Internal array of tiles represented by unique pointers
    static std::unique_ptr<TILE[]> _tiles;
    // Static members to hold the width and height of the level in tiles
    static size_t _width;
    static size_t _height;
    // Offset for rendering the level on the screen
    static sf::Vector2f _offset;
    // Size of each tile when rendered on the screen
    static float _tileSize;
    // Map to associate tile types with colors for rendering
    static std::map<TILE, sf::Color> _colours;

    // Vector of unique pointers to sf::RectangleShape for each tile's sprite
    static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;
    // Function to build the sprites based on current level data
    static void buildSprites();

private:
    // Private constructors to prevent instantiation of the class
    LevelSystem() = delete;
    ~LevelSystem() = delete;
};
