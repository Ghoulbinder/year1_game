//player.cpp
#include "player.h"
#include "LevelSystem.h"
using namespace sf;
using namespace std;


bool Player::validMove(sf::Vector2f pos) {
    // Calculate the tile position of the potential new position
    sf::Vector2ul tilePos = {
        static_cast<size_t>(pos.x / ls::getTilePosition({ 0, 0 }).x),
        static_cast<size_t>(pos.y / ls::getTilePosition({ 0, 0 }).y)
    };
    // Debug output
    cout << "Checking tile at position: (" << tilePos.x << ", " << tilePos.y << ")" << endl;

    // Check if the tile at the new position is not a wall
    if (ls::getTile(tilePos) != ls::WALL) {
        cout << "Valid move!" << endl;
        return true;
    }
    else {
        cout << "Invalid move! It's a wall." << endl;
        return false;
    }
    // Check if the tile at the new position is not a wall
    return ls::getTile(tilePos) != ls::WALL;
}

void Player::Update(double dt) {
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        sf::Vector2f newPos = _shape->getPosition();
        newPos.y -= _speed * static_cast<float>(dt);
       if (validMove(newPos)) {
           _shape->move(0.0f, -_speed * static_cast<float>(dt)); // Move up
           cout << "Moving up to position: " << _shape->getPosition().x << ", " << _shape->getPosition().y << endl;
       }
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        sf::Vector2f newPos = _shape->getPosition();
        newPos.y += _speed * static_cast<float>(dt);
        if (validMove(newPos)) {
            _shape->move(0.0f, _speed * static_cast<float>(dt)); // Move down
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        sf::Vector2f newPos = _shape->getPosition();
        newPos.x -= _speed * static_cast<float>(dt);
        if (validMove(newPos)) {
            _shape->move(-_speed * static_cast<float>(dt), 0.0f); // Move left
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        sf::Vector2f newPos = _shape->getPosition();
        newPos.x += _speed * static_cast<float>(dt);
       if (validMove(newPos)) {
           _shape->move(_speed * static_cast<float>(dt), 0.0f); // Move right
       }
    }

  

        Entity::Update(dt);
}



Player::Player()
    : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
    _shape->setFillColor(Color::Magenta);
    _shape->setOrigin(Vector2f(25.f, 25.f));
    _shape->setPosition(Vector2f(135.f, 154.f)); // Set the player's starting position to (400, 300)
}

void Player::Render(sf::RenderWindow& window) const {
    window.draw(*_shape);
}

