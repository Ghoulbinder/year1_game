// game.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Entity;
class Bullet; // forward-declare Bullet
class Mage;   // Forward-declare Mage

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 12;

extern sf::Texture spritesheet;
extern std::vector< Entity*> ships;
extern Entity* player;
extern std::vector<Bullet*> bullets;

extern Mage* playerMage; // Declare playerMage
