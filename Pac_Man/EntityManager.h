// EntityManager.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Entity;

class EntityManager {
public:
    std::vector<std::shared_ptr<Entity>> list;
    void update(double dt);
    void render(sf::RenderWindow& window);
    //const std::vector<std::shared_ptr<Entity>>& getList() const {
    //    return list;
    //}
protected:
    //std::vector<std::shared_ptr<Entity>> list;
};
