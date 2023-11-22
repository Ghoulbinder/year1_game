// Include the corresponding header file for the Entity class definitions.
#include "entity.h"

// Use the standard and SFML namespaces to avoid prefixing their classes/functions with std:: and sf::.
using namespace std;
using namespace sf;

// Retrieve the current position of the entity.
const Vector2f Entity::getPosition() { return _position; }

// Set the entity's position to a new value.
void Entity::setPosition(const Vector2f& pos) { _position = pos; }

// Move the entity's position by a certain offset.
void Entity::move(const Vector2f& pos) { _position += pos; }

// Update the entity's position to match the shape's position.
void Entity::Update(const double dt) {
    setPosition(_shape->getPosition());
}

// Constructor for the Entity, takes ownership of a Shape pointer.
Entity::Entity(unique_ptr<Shape> s) : _shape(std::move(s)) {}

