// EntityManager.cpp
#include "EntityManager.h"
#include "Entity.h"

void EntityManager::update(double dt) {
    for (const auto& entity : list) {
        entity->Update(dt);
    }
}

void EntityManager::render(sf::RenderWindow& window) {
    for (const auto& entity : list) {
        entity->Render(window);
    }
}
