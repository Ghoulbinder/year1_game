#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"
#include "bullet.h"


using namespace std;
using namespace sf;

std::vector<Ship*> ships;
sf::Texture spritesheet;
sf::Sprite invader;
Ship* player = nullptr;
std::vector<Bullet*> bullets;


void Load() {
    if (!spritesheet.loadFromFile("C:/Users/romeo/year1_game/res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    // Load and position the first 6 invaders, assuming they are 32x32 sprites in the top row.
    for (int i = 0; i < invaders_rows; ++i) {
        for (int j = 0; j < 6; ++j) { // Only the first 6 aliens in the row
            Vector2f pos(100 + j * 50, 100 + i * 50); // positioning
            // Calculate the texture rectangle for each invader based on its position in the sprite sheet
            int textureX = j * 32; // X position based on column
            int textureY = 0; // Y position is 0 because invaders are on the top row
            Invader* inv = new Invader(IntRect(Vector2i(textureX, textureY), Vector2i(32, 32)), pos);
            ships.push_back(inv);
        }
    }

    // Initialize the player ship
    player = new Player();// (IntRect(Vector2i(0, 32), Vector2i(32, 32))); // Assuming player sprite is next on spritesheet
    player->setPosition({ gameWidth / 2, gameHeight - 50 }); // Position the player at the bottom center
    ships.push_back(player);
}

void Render(RenderWindow& window) {
    for (const auto& ship : ships) {
        window.draw(*ship);
    }
}

int main(){
  sf::RenderWindow window(sf::VideoMode({ 600, 500 }), "SFML works!");
  sf::CircleShape shape(100.f);
  //shape.setFillColor(sf::Color::Green);
  Load();
  while (window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }

      static Clock clock;                           // Declare a static clock to measure time intervals.
      float dt = clock.restart().asSeconds();       // Restart the clock and get the elapsed time in seconds.
   
      window.clear();

      Render(window);
     for (auto& bullet : bullets) {
         bullet->Update(dt);
     }
      for (auto& s : ships) {
          s->Update(dt);
      };
      // Render bullets
      for (auto& bullet : bullets) {
          window.draw(*bullet);
      }

      // Cleanup bullets
      bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* b) {
          return b->getPosition().y < 0 || b->getPosition().y > gameHeight;
          }), bullets.end());
  
      window.display();
    }

  for (auto* bullet : bullets) {
      delete bullet;
  }

  bullets.clear();

  //delete the dynamically allocated ships
  for (auto& ship : ships) {
      delete ship;
  }


  return 0;
}