// ship.cpp
#include "ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

bool Invader::direction;
float Invader::speed;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 


Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(Vector2f(16.f, 16.f));;
	setPosition(pos);
}

void Invader::Update(const float& dt) {
	Ship::Update(dt);
	move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

	if ((direction && getPosition().x > gameWidth - 16) ||
		(!direction && getPosition().x < 16)) {
		direction = !direction;
		for (int i = 0; i < ships.size(); ++i) {
			ships[i]->move(Vector2f(0.0f, 24.0f));
		}

	}
}

vector<Bullet*> bullets; // Declare bullets vector

bool Ship::is_exploded() const {
	return _exploded;
}

void Ship::Explode() {
	setTextureRect(IntRect(Vector2i(128, 32), Vector2i(32, 32)));
	_exploded = true;
}

Ship::~Ship() {
	// Implementation of pure virtual destructor, even if it's empty
}

bool Invader::is_exploded() const {
	// Specific behavior for Invader if necessary, otherwise just call the base implementation
	return Ship::is_exploded();
}

void Invader::Explode() {
	// Specific behavior for Invader explosion
	Ship::Explode(); // Optionally call the base class method
	// Additional Invader-specific explosion logic
}

Player::Player() : Ship(IntRect(Vector2i(160, 32), Vector2i(32, 32))) {
	//setOrigin(Vector2f(16.f, 16.f)); // Center the origin if needed for rotation, etc.

	setPosition({ gameWidth * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
	Ship::Update(dt);

	static float firetime = 0.0f;
	firetime -= dt;

	if (firetime <= 0 && Keyboard::isKeyPressed(Keyboard::Space)) {
		Bullet::Fire(getPosition(), false);
		firetime = 0.7f;

		// Move left
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			// Calculate new position to move to, ensuring the player does not move off-screen
			float newX = max(0.0f, getPosition().x - (speed * dt));
			setPosition({ newX, getPosition().y });
		}

		// Move right
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			// Calculate new position to move to, ensuring the player does not move off-screen
			float newX = min(gameWidth - getLocalBounds().width, getPosition().x + (speed * dt));
			setPosition({ newX, getPosition().y });
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			// Fire a bullet from the player's position
			bullets.push_back(new Bullet(getPosition(), false));
		}

		// Update bullets
		for (const auto& b : bullets) {
			b->Update(dt);
		}
	}
}
