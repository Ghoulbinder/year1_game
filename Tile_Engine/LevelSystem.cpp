// Include the necessary headers and declare usage of standard and SFML namespaces
#include "LevelSystem.h"
#include "maths.h"
#include "player.h"          // Include the header for the player character.
#include "Entity.h"   
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace sf;

// Static member initialization for the LevelSystem class
unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
Vector2f LevelSystem::_offset(0.0f, 0.0f);
float LevelSystem::_tileSize(50.f);
vector<unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;
std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{ {WALL, Color::White}, {END, Color::Red} };

// Method to get the color for a specific tile type, adding Transparent color if not found
Color LevelSystem::getColor(LevelSystem::TILE t) {
    auto it = _colours.find(t);
    if (it == _colours.end()) {
        _colours[t] = Color::Transparent;
    }
    return _colours[t];
}

// Method to set the color for a specific tile type
void LevelSystem::setColor(LevelSystem::TILE t, Color c) {
    _colours[t] = c;
}



// Method to construct the sprite representations of the tiles
void LevelSystem::buildSprites() {
    // Clear the current sprites
    _sprites.clear();

    // Loop through every tile in the grid
    for (size_t y = 0; y < _height; ++y) {
        for (size_t x = 0; x < _width; ++x) {
            // Get the type of the current tile
           // TILE tileType = _tiles[x + y * _width];

            // Create a new RectangleShape to represent the tile visually
            auto sprite = make_unique<RectangleShape>(Vector2f(_tileSize, _tileSize));
            sprite->setPosition(getTilePosition(Vector2ul(x, y))); // Set the position based on the tile coordinates
            sprite->setFillColor(getColor(getTile({ x, y }))); // Set the fill color based on the tile type

            // Add any additional visual configurations here
            // For example, you might want to add a texture or outline

            // Add the sprite to the list of sprites
            _sprites.push_back(move(sprite));
        }
    }
}
// Method to load a level from a file and parse its tiles

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
    _tileSize = tileSize;
    size_t w = 0, h = 0;
    string buffer;

    // Load in file to buffer
    ifstream f("C:\\Users\\romeo\\year1_game\\res\\levels\\maze_2.txt");
    if (f.good()) {
        f.seekg(0, std::ios::end);
        buffer.resize(f.tellg());
        f.seekg(0);
        f.read(&buffer[0], buffer.size());
        f.close();
    }
    else {
        throw string("Couldn't open level file: ") + "C:\\Users\\romeo\\year1_game\\res\\levels\\maze_2.txt";
    }

    std::vector<TILE> temp_tiles;
    for (int i = 0; i < buffer.size(); ++i) {
        const char c = buffer[i];
        switch (c) {
        case 'w':
            temp_tiles.push_back(WALL);
            break;
        case 's':
            temp_tiles.push_back(START);
            break;
        case 'e':
            temp_tiles.push_back(END);
            break;
        case ' ':
            temp_tiles.push_back(EMPTY);
            break;
        case '+':
            temp_tiles.push_back(WAYPOINT);
            break;
        case 'n':
            temp_tiles.push_back(ENEMY);
            break;
        case '\n':      // end of line
            if (w == 0) { // if we haven't written width yet
                w = i;      // set width
            }
            h++; // increment height
            break;
        default:
            cout << c << endl; // Don't know what this tile type is
        }
    }
    if (temp_tiles.size() != (w * h)) {
        throw string("Can't parse level file") + path;
    }
    _tiles = std::make_unique<TILE[]>(w * h);
    _width = w; //set static class vars
    _height = h;
    std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
    cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
    buildSprites();
}

// Method to get the position of a tile in the level
Vector2f LevelSystem::getTilePosition(Vector2ul p) {
    return (Vector2f(p.x, p.y) * _tileSize);
}

LevelSystem::TILE LevelSystem::getTileAt(sf::Vector2f v) {
    // Adjust v by the offset to find the correct tile
    auto a = (v - _offset) / _tileSize;
    // Convert the float coordinates to unsigned long, ensuring they are within the level's range
    if (a.x < 0 || a.y < 0) {
        throw std::string("Tile out of range\n");
    }
    // Cast to unsigned long to use as indices
    sf::Vector2ul tileIndex(static_cast<unsigned long>(a.x), static_cast<unsigned long>(a.y));

    // Now call getTile with the correct type
    return getTile(tileIndex);
}
LevelSystem::TILE LevelSystem::getTile(sf::Vector2ul position) {
    // Check if the position is within the bounds of the level
    if (position.x >= _width || position.y >= _height) {
        //throw std::string("Tile out of range\n");//neeed looking into
    }
    // Calculate the index based on the width and the position
    size_t index = position.y * _width + position.x;
    // Return the tile at the calculated index
    return _tiles[index];
}

// Method to render all the tiles as sprites in the window
void LevelSystem::Render(RenderWindow& window) {
    for (const auto& sprite : _sprites) {
        window.draw(*sprite);
    }
}
