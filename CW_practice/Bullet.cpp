#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "Game.h"
#include "Entity.h"

using namespace sf;
using namespace std;



unsigned char Bullet::bulletPointer = 0;
Bullet Bullet::bullets[256];
std::vector<Entity*> entities;





// Default constructor (might be private if you only create bullets through Fire method)
Bullet::Bullet() {
    std::cout << "Constructing a Bullet" << std::endl;
    _active = false; // Initialize to inactive by default
}

Bullet::Bullet(const sf::Vector2f& pos, const bool mode) : _mode(mode) {
    setTexture(spritesheet);
    setPosition(pos);

}


void Bullet::Update(const float& dt) {
    for (unsigned char i = 0; i < bulletPointer; ++i) {
        if (bullets[i].isActive()) {
            // Move each active bullet
            bullets[i].move(Vector2f(0, dt * 200.0f * (bullets[i]._mode ? 1.0f : -1.0f)));

            // Check if the bullet is off-screen
            if (bullets[i].getPosition().y < -32 || bullets[i].getPosition().y > gameHeight + 32) {
                // Deactivate off-screen bullet
                bullets[i]._active = false; // Assuming _active is a member that tracks if a bullet is active
            }
            else {
                // Check for collision with ships
                const FloatRect boundingBox = bullets[i].getGlobalBounds();
                for (auto s : entities) {
                    // Make sure 'player' is a defined pointer to the player's ship
                    for (auto s : entities) {
                        // Assuming 'player' is of type 'Entity*' or a derived class of 'Entity'
                        if (!bullets[i]._mode && s == playerMage) {
                            continue;
                        }
                        if (bullets[i]._mode && s != playerMage) {
                            continue;
                        }
                        if (!s->is_exploded() && s->getGlobalBounds().intersects(boundingBox)) {
                            // Explode the ship
                            s->Explode();
                            // Warp bullet off-screen
                            bullets[i].setPosition(Vector2f(-100, -100));
                            bullets[i]._active = false; // Deactivate the bullet
                            break; // Exit the loop as the bullet has hit a ship
                        }
                    }
                }
            }
        }
    }
}

// Static method to render all bullets in the pool
void Bullet::Render(sf::RenderWindow& window) {
    for (unsigned char i = 0; i < bulletPointer; ++i) {
        if (bullets[i].isActive()) {
            window.draw(bullets[i]);
        }
    }
}

void Bullet::Init() {
    std::cout << "Initializing bullets..." << std::endl;
    for (unsigned char i = 0; i < 256; ++i) {
        std::cout << "Constructing bullet " << static_cast<int>(i) << std::endl;
        bullets[i] = Bullet(); // Calls the default constructor
        bullets[i].setPosition(-100, -100);
    }
    std::cout << "Bullet initialization completed." << std::endl;
}



void Bullet::Fire(const sf::Vector2f& pos, const bool mode) {
    unsigned char start = bulletPointer;
    bool allActive = true;

    do {
        if (!bullets[bulletPointer].isActive()) {
            bullets[bulletPointer].setPosition(pos);
            bullets[bulletPointer]._mode = mode;
            bullets[bulletPointer]._active = true;
            allActive = false;
            break;
        }

        bulletPointer++;
        if (bulletPointer >= 256) {
            bulletPointer = 0;
        }
    } while (bulletPointer != start);

    if (allActive) {
        std::cerr << "All bullets are active, unable to fire a new one." << std::endl;
        // Handle the situation when all bullets are active (e.g., skip firing a bullet)
        return;
    }

    bulletPointer++;
    if (bulletPointer >= 256) {
        bulletPointer = 0;
    }
}

// a method to determine if a bullet is active
bool Bullet::isActive() const {
    //bullet is considered active if it's within the screen boundaries
    return getPosition().x >= 0 && getPosition().x <= gameWidth &&
           getPosition().y >= 0 && getPosition().y <= gameHeight && _active;

}