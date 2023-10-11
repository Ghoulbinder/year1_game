//ghost.cpp
#include "ghost.h"
using namespace sf;
using namespace std;


Ghost::Ghost()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Red);
    _shape->setOrigin(Vector2f(25.f, 25.f));

    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));
}

 
void Ghost::Update(double dt) {

    // Make the ghost move randomly
    int dx = (rand() % 3) - 1; // Generates a random number between -1 and 1
    int dy = (rand() % 3) - 1; // Generates a random number between -1 and 1
    sf::Vector2f offset(dx * dt, dy * dt);

    move(offset);

    Entity::Update(dt);
}


void Ghost::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}