// ship.cpp
#include "Ship.h"
#include "Game.h"
#include "Bullet.h"
#include "Mage.h"

using namespace sf;
using namespace std;


Ship::Ship() {};

//constructor with an initialization list
Ship::Ship(sf::IntRect ir, sf::Vector2f pos) : _sprite() {
    _sprite = ir;
    setTexture(spritesheet);
    setTextureRect(_sprite);
    setPosition(pos);
    // Initialize other member variables if needed
}


void Ship::Update(const float& dt) {}

Ship::~Ship() {
    // Implementation of pure virtual destructor, even if it's empty
}

bool Ship::is_exploded() const {
    return _exploded;
}

void Ship::Explode() {
    setTextureRect(IntRect(Vector2i(128, 32), Vector2i(32, 32)));
    _exploded = true;
}

