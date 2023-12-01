#pragma once
#include <functional>
#include "cmp_player_movement.h"
#include "Entity.h"

class EnemyAIComponent : public ActorMovementComponent {
private:
    std::function<sf::Vector2f()> _getPlayerPosition;
    float _enemySpeed;

public:
    EnemyAIComponent(Entity* p, std::function<sf::Vector2f()> getPlayerPosition, float ghostSpeed);



    void update(const float& dt) override;
};