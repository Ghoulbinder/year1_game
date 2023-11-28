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

// Default constructor
Bullet::Bullet() : _active(false), _mode(false) {
    setPosition(-100, -100); // Initialize with off-screen position
}

Bullet::Bullet(const Vector2f& pos, const bool mode) : _mode(mode), _active(true) {
    setTexture(spritesheet); // Assuming spritesheet is globally accessible
    setPosition(pos);
}

void Bullet::Update(const float& dt) {
    for (auto& bullet : bullets) {
        if (bullet.isActive()) {
            // Move bullet
            float direction = bullet.getMode() ? 1.0f : -1.0f; // Assuming getMode() is a method to access _mode
            bullet.move(0, dt * 200.0f * direction);

            // Check off-screen
            if (bullet.getPosition().y < -32 || bullet.getPosition().y > gameHeight + 32) {
                bullet.deactivate();
            }
            else {
                bullet.checkCollisions(); // Assuming checkCollisions is a method of Bullet
            }
        }
    }
}

bool Bullet::getMode() const {
    return _mode;
}

void Bullet::checkCollisions() {
    // Implement collision logic here
}


void Bullet::Render(RenderWindow& window) {
    for (const auto& bullet : bullets) {
        if (bullet.isActive()) {
            window.draw(bullet);
        }
    }
}

void Bullet::Init() {
    cout << "Initializing bullets..." << endl;
    for (auto& bullet : bullets) {
        bullet.deactivate();
    }
    cout << "Bullet initialization completed." << endl;
}

void Bullet::Fire(const Vector2f& pos, const bool mode) {
    Bullet& bullet = bullets[bulletPointer];
    if (!bullet.isActive()) {
        bullet.activate(pos, mode);
    }

    bulletPointer = (bulletPointer + 1) % 256;
}

bool Bullet::isActive() const {
    return _active;
}

void Bullet::checkCollisions(Bullet& bullet) {
    FloatRect boundingBox = bullet.getGlobalBounds();
    for (auto* entity : entities) {
        if ((bullet._mode && entity != playerMage) || (!bullet._mode && entity == playerMage)) {
            continue;
        }

        if (entity->is_exploded()) {
            continue;
        }

        if (entity->getGlobalBounds().intersects(boundingBox)) {
            entity->Explode();
            bullet.deactivate();
            break;
        }
    }
}

void Bullet::activate(const Vector2f& pos, bool mode) {
    setPosition(pos);
    _mode = mode;
    _active = true;
}

void Bullet::deactivate() {
    setPosition(-100, -100);
    _active = false;
}
