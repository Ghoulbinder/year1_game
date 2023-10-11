//ghost.h
#pragma once
#include "entity.h"

class Ghost : public Entity {
private:
	float _speed;

public:
	void Update(double dt) override;
	Ghost();
	void Render(sf::RenderWindow& window) const override;
};
