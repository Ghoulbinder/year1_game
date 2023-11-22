//entity.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>


class Entity {
protected:
	std::unique_ptr<sf::Shape> _shape;
	sf::Vector2f _position;
	Entity(std::unique_ptr<sf::Shape> shp);

public:
	Entity() = delete;
	virtual ~Entity() = default;

	//sf::Shape* getShape() const { return _shape.get(); }

	virtual void Update(double dt);
	virtual void Render(sf::RenderWindow& window) const = 0;

	const sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f& pos);
	void move(const sf::Vector2f& pos);

	

};


