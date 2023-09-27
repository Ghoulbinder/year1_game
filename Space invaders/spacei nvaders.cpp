#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    // Initialize window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Invaders");

    // Initialize player
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.f, 500.f);

    // Initialize enemies
    std::vector<sf::RectangleShape> enemies;
    for(int i = 0; i < 5; ++i) {
        sf::RectangleShape enemy(sf::Vector2f(50.f, 50.f));
        enemy.setFillColor(sf::Color::Red);
        enemy.setPosition(i * 60.f, 0.f);
        enemies.push_back(enemy);
    }

    // Initialize bullets
    std::vector<sf::RectangleShape> bullets;

    // Main loop
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // Player movement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-0.1f, 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(0.1f, 0.f);

        // Shooting
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            sf::RectangleShape bullet(sf::Vector2f(5.f, 10.f));
            bullet.setFillColor(sf::Color::Yellow);
            bullet.setPosition(player.getPosition().x + 22.f, player.getPosition().y);
            bullets.push_back(bullet);
        }

        // Bullet movement
        for(auto& bullet : bullets) {
            bullet.move(0.f, -0.1f);
        }

        // Enemy movement
        for(auto& enemy : enemies) {
            enemy.move(0.f, 0.01f);
        }

        // Collision detection
        for(auto& bullet : bullets) {
            for(auto& enemy : enemies) {
                if(bullet.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                    bullet.setFillColor(sf::Color::Transparent);
                    enemy.setFillColor(sf::Color::Transparent);
                }
            }
        }

        // Drawing
        window.clear();
        window.draw(player);

        for(const auto& enemy : enemies) {
            window.draw(enemy);
        }

        for(const auto& bullet : bullets) {
            window.draw(bullet);
        }

        window.display();
    }
    return 0;
}
