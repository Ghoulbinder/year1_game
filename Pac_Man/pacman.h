#pragma once
#include <memory>
#include "scene.h"
#include "player.h"
#include "ghost.h"



class MenuScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	

public:
	MenuScene() = default;
	void update(double dt) override;
	void render(sf::RenderWindow& window) override;
	void load()override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	void update(double dt) override;
	void render(sf::RenderWindow& window) override;
	void load() override;

};

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;