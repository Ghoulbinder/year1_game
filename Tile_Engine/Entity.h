// Use of #pragma once to ensure the header is only included once during compilation
#pragma once

// Include the necessary header files from SFML for graphics
#include <SFML/Graphics.hpp>
// Include the memory header for smart pointer utilities
#include <memory>

// Declaration of the Entity class
class Entity {
protected:
    // A smart pointer to an SFML Shape that represents the Entity's graphical shape
    std::unique_ptr<sf::Shape> _shape;
    // A Vector2f to hold the position of the Entity
    sf::Vector2f _position;
    // Protected constructor that initializes an Entity with a shape
    Entity(std::unique_ptr<sf::Shape> shp);

public:
    // Delete the default constructor to prevent instantiation without a shape
    Entity() = delete;
    // Virtual default destructor for proper cleanup of derived classes
    virtual ~Entity() = default;

    // Virtual Update method to be overridden by derived classes, for updating logic
    virtual void Update(const double dt);
    // Pure virtual Render method to be implemented by derived classes, for drawing the Entity
    virtual void Render(sf::RenderWindow& window) const = 0;

    // Getter method for the position of the Entity
    const sf::Vector2f getPosition();
    // Setter method to set the position of the Entity
    void setPosition(const sf::Vector2f& pos);
    // Method to move the Entity by a given offset
    void move(const sf::Vector2f& pos);
};
