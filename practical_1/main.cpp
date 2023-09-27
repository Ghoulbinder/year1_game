#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {

    Keyboard::A,  //player 1 UP
    Keyboard::Z,   //PLayer 1 Down
    Keyboard::Up,  //Player 2 Up
    Keyboard::Down,  //PLayer 2 Down

};

CircleShape ball;
RectangleShape paddles[2];

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
Vector2f ballVelocity;
bool isPlayer1Serving = false;
const float initialVelocityX = 100.f;
const float initialVelocityY = 60.f;
const float velocityMultiplier = 1.1f;




//sf::Font font;  // Declare a Font variable
//sf::Text text;  // Declare a Text variable for the score display
int player1Score = 0, player2Score = 0;  // Scores for the two players


void Reset() {
    // Reset ball to center of the screen
    ball.setPosition(sf::Vector2f(gameWidth / 2.f, gameHeight / 2.f));

    // Flip serving player to alternate who serves
    isPlayer1Serving = !isPlayer1Serving;

    // Reset ball velocity to initial velocity and flip X-direction if player 2 is serving
    ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };

    //std::stringstream ss;
    //ss << player1Score << " - " << player2Score;
    //text.setString(ss.str());
    //
    //// Center the text
    //text.setPosition(sf::Vector2f((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0));
}

void load() {
    //set seize and origin of paddle
    for (auto& p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f);
    }
    //Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(sf::Vector2f(10.f,10.f));

    paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2f(gameWidth - (paddleOffsetWall +paddleSize.x) / 2.f, gameHeight / 2.f));
    ball.setPosition(sf::Vector2f(gameWidth / 2.f, gameHeight / 2.f ));

    ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };

    // Load font-face from res dir
    //if (!font.loadFromFile("C:/Users/romeo/year1_game/res/Roboto-Black.ttf")) {
    //    cout << "Failed to load font" << endl;
    //}
    //// Set text element to use font
    //text.setFont(font);
    //// set the character size to 24 pixels
    //text.setCharacterSize(24);
    //text.setString("0 - 0");  // Initial score display

}



void Update(RenderWindow& window) {

    //reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    //check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    // check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;

    ball.move(ballVelocity * dt);

    //quit via Esc Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    // Handle first paddle movement
    float direction1 = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction1--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction1++;
    }
    paddles[0].move(Vector2f(0.f, direction1 * paddleSpeed * dt));

    // Handle second paddle movement
    float direction2 = 0.0f;
    if (Keyboard::isKeyPressed(controls[2])) {
        direction2--;
    }
    if (Keyboard::isKeyPressed(controls[3])) {
        direction2++;
    }
    paddles[1].move(Vector2f(0.f, direction2 * paddleSpeed * dt));
 
    if (by > gameHeight) { //bottom wall
        // bottom wall
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(Vector2(0.f, -10.f));
    }
    else if (by < 0) { //top wall
        // top wall
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(Vector2(0.f, 10.f));
    }
    else if (bx > gameWidth) {
        // right wall
        Reset();
    }
    else if (bx < 0) {
        // left wall
        Reset();
    }


    else if (
        //ball is inline or behind paddle AND
        bx < paddleSize.x + paddleOffsetWall &&
        //ball is below top edge of paddle AND
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
        )
    {
        cout << "Collision with left paddle detected!" << endl;
        // bounce off left paddle
        ballVelocity.x = -ballVelocity.x * velocityMultiplier;
    }
    else if (
        //ball is inline or ahead of paddle AND
        bx > gameWidth - (paddleSize.x + paddleOffsetWall) &&
        //ball is below top edge of paddle AND
        by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
        //ball is above bottom edge of paddle
        by < paddles[1].getPosition().y + (paddleSize.y * 0.5)
        )
    {
        cout << "Collision with  paddle detected!" << endl;
        // bounce off right paddle
        ballVelocity.x = -ballVelocity.x * velocityMultiplier;
    }


}



    void Render(RenderWindow & window) {
        // Draw Everything
        window.draw(paddles[0]);
        window.draw(paddles[1]);
        window.draw(ball);
        //window.draw(text);
    }
      



int main(){
    RenderWindow window(sf::VideoMode({ gameWidth, gameHeight }), "SFML works!");
    load();
  while (window.isOpen()){

    window.clear();
    Update(window);
    Render(window);
    window.display();
  }
  return 0;
}