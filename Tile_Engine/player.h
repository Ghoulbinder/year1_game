// This ensures the header is only included once during compilation to prevent redefinition errors.
#pragma once

// Include the definition of the Entity class so Player can inherit from it.
#include "entity.h"

// Define the Player class which inherits from Entity class
class Player : public Entity {
private:
    float _speed; // Private variable to hold the player's speed.

    // Private method to check if a move is valid
    bool validMove(sf::Vector2f pos);

public:
    // Override the Update method from Entity to implement player-specific update logic
    void Update(double dt) override;

    // Constructor declaration for the Player class
    Player();

    // Override the Render method from Entity to implement how the player is drawn on the window
    void Render(sf::RenderWindow& window) const override;
};
