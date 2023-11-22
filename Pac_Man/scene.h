//scene.h
#include "entity.h"
#include "EntityManager.h"

#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    void loadFont() {
        if (!font.loadFromFile("C:\\Users\\romeo\\year1_game\\res\\fonts\\Roboto-Black.ttf")) {
            // Handle font loading error
            std::cout << "Error: Font file not found or failed to load!" << std::endl;
        }
    }

    // Update function to update entities in the scene
    virtual void update(double dt) {
     
    }

    // Render function to render entities in the scene
    virtual void render(sf::RenderWindow& window); //{


    // Pure virtual load function to be implemented by derived classes
    virtual void load() = 0;


    // Getter to access the entity list
    std::vector<std::shared_ptr<Entity>>& getEnts();



protected:
    sf::Font font;
    EntityManager _ents;
    bool isLoading = false; // Flag to indicate if loading screen is active
};

#endif // SCENE_H