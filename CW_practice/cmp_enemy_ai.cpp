#include "Entity.h"
#include "cmp_enemy_ai.h"
#include "LevelSystem.h"
#include "cmp_player_movement.h"
#include <cmath>
#include <iostream>

using namespace sf;

// Function prototypes for normalize and length 
Vector2f normalize(const Vector2f & v);  
float length(const Vector2f & v);

EnemyAIComponent::EnemyAIComponent(Entity* p, std::function<sf::Vector2f()> getPlayerPosition, float enemySpeed)
    : ActorMovementComponent(p), _getPlayerPosition(getPlayerPosition), _enemySpeed(enemySpeed) {}

void EnemyAIComponent::update(const float& dt) {
    const auto mva = (float)(dt * _enemySpeed); // Using the ghost's speed
    const sf::Vector2f pos = _parent->getPosition();

    // Get the player's current position
    sf::Vector2f playerPos = _getPlayerPosition();

    // Calculate direction towards the player
    Vector2f direction = playerPos - pos;
    if (length(direction) > 0) {
        direction = normalize(direction);
    }

    // Move the enemy
    _parent->move(direction * mva);

    // Convert Vector2f to Vector2ul for LevelSystem
    sf::Vector2i intPos = static_cast<sf::Vector2i>(pos); // First convert to Vector2i
    sf::Vector2ul tilePosition(static_cast<unsigned long>(intPos.x), static_cast<unsigned long>(intPos.y)); // Then to Vector2ul

    // Check the TILE type
    if (LevelSystem::getTile(tilePosition) == LevelSystem::TILE::WALL) {
        // Handle collision with wall
    }
}





// Utility function to normalize a vector
Vector2f normalize(const Vector2f& v) {
    float len = length(v);
    if (len != 0) {
        return v / len;
    }
    return v;
}

// Utility function to calculate the length of a vector
float length(const Vector2f& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}


