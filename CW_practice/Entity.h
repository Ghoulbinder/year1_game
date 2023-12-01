//Entity.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"


class Entity : public sf::Sprite {
protected:
    sf::IntRect _sprite;
    sf::Texture _texture;
    //Default constructor is hidden
    Entity();
public:
  
    static bool direction;
    static float speed;
    //Constructor that takes a sprite
    explicit Entity(sf::IntRect ir, sf::Vector2f pos, sf::Texture& texture); 
    //Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour!
    virtual ~Entity() = 0;
    //Update, virtual so can be overridden, but not pure virtual
    virtual void Update(const float& dt);
};


class Mage : public Entity {
public:
    Mage(); // Default constructor declaration
    Mage(sf::IntRect ir, sf::Vector2f pos, sf::Texture& texture);
    void Update(const float& dt) override;
    void FireBullet(bool mode, const sf::Vector2f& direction);

private:
    Animation walkDownAnimation;
    Animation walkUpAnimation;
    Animation walkLeftAnimation;
    Animation walkRightAnimation;

    //std::shared_ptr<ActorMovementComponent> _movement;
    // Enumeration for directions
    enum class Direction { Up, Down, Left, Right };
    Direction currentDirection = Direction::Down; // Default direction

    // Speed of the mage
    float speed;
};


class Slime : public Entity {
public:
    Slime();
    Slime(sf::IntRect ir, sf::Vector2f pos, sf::Texture& texture);
    void Update(const float& dt) override;
    void FireBullet(bool mode, const sf::Vector2f& direction);


private:
    Animation* currentAnimation; // Declare currentAnimation as a pointer to Animation
    Animation idleAnimation;
    Animation attackAnimation;
    Animation movingAnimation;
    float _speed;
};



