//"cmp_player_movement.cpp"
#include "cmp_player_movement.h"
#include "LevelSystem.h"


using namespace sf;

ActorMovementComponent::ActorMovementComponent(Entity* p) : _speed(100.f) {
    setParent(p); // Associate the parent entity
}

// ... rest of your implementation ...



bool ActorMovementComponent::validMove(const sf::Vector2f& pos) {
    sf::Vector2i intPos = static_cast<sf::Vector2i>(pos); // Convert to Vector2i
    sf::Vector2ul ulPos(static_cast<unsigned long>(intPos.x), static_cast<unsigned long>(intPos.y)); // Convert to Vector2ul

    return (LevelSystem::getTile(ulPos) != LevelSystem::WALL);
}


void ActorMovementComponent::move(const sf::Vector2f& p) {
    auto pp = _parent->getPosition() + p;
    if (validMove(pp)) {
        _parent->setPosition(pp);
    }
}

void ActorMovementComponent::move(float x, float y) {
    move(Vector2f(x, y));
}
float ActorMovementComponent::getSpeed() const { 
    return _speed; 
}

void ActorMovementComponent::setSpeed(float speed) { 
    _speed = speed; 
}

void ActorMovementComponent::update(const float& dt) {
    float speed = getSpeed() * dt;

    if (Keyboard::isKeyPressed(Keyboard::W)) {
        move(Vector2f(0.f, -speed));
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        move(Vector2f(-speed, 0.f));
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        move(Vector2f(0.f, speed));
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        move(Vector2f(speed, 0.f));
    }
}