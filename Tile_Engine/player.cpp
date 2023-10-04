//player.cpp
#include "player.h"
using namespace sf;
using namespace std;

void Player::Update(double dt) {
   
     // Move in four directions based on keys
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        _shape->move(0.0f, -_speed * dt); // Move up
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        _shape->move(0.0f, _speed * dt); // Move down
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        _shape->move(-_speed * dt, 0.0f); // Move left
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        _shape->move(_speed * dt, 0.0f); // Move right
    }

  

        Entity::Update(dt);
}

Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}