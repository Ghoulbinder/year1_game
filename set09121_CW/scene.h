//scene.h
#pragma once
#include "ecm.h"
class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void update(double dt) {};
	virtual void render() {};
	virtual void load() = 0;
	std::vector<std::shared_ptr<Entity>>& getEnts();
	void addEntity(std::shared_ptr<Entity> entity);

protected:
	EntityManager _ents;

};