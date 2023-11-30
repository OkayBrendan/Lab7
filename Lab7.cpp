#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {
    // Create a window with a size of 800x600 pixels and title 'Bounce'
    RenderWindow window(VideoMode(800, 600), "Bounce");
    // Create a physics world with a downward gravity (0, 1)
    World world(Vector2f(0, 1));

    // Create a ball as a physics circle, set its center and radius
    PhysicsCircle ball;
    ball.setCenter(Vector2f(100, 300));
    ball.setRadius(20);
    // Add the ball to the physics world
    world.AddPhysicsBody(ball);
    // Apply an initial impulse to the ball for movement
    ball.applyImpulse(Vector2f(1, -1));

    // Create a floor as a physics rectangle, set its size and center
    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    // Make the floor static (immovable)
    floor.setStatic(true);
    // Add the floor to the physics world
    world.AddPhysicsBody(floor);

    // Create walls and ceiling as physics rectangles
    PhysicsRectangle leftWall, rightWall, ceiling;

    // Set up the left wall
    leftWall.setSize(Vector2f(20, 600));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);

    // Set up the right wall
    rightWall.setSize(Vector2f(20, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);

    // Set up the ceiling
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);

    // Add the walls and ceiling to the physics world
    world.AddPhysicsBody(leftWall);
    world.AddPhysicsBody(rightWall);
    world.AddPhysicsBody(ceiling);

    // Create a center obstacle as a physics rectangle
    PhysicsRectangle centerObstacle;
    centerObstacle.setSize(Vector2f(100, 100));
    centerObstacle.setCenter(Vector2f(400, 300));
    centerObstacle.setStatic(true);
    // Add the center obstacle to the physics world
    world.AddPhysicsBody(centerObstacle);

    // Initialize counters for collision events
    int thudCount(0), bangCount(0);

    // Define collision handling for the floor
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };

    // Define collision handling for the left wall
    leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };

    // Define collision handling for the right wall
    rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };

    // Define collision handling for the ceiling
    ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
        };

    // Define special collision handling for the center obstacle
    centerObstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        cout << "bang " << bangCount << endl;
        bangCount++;
        if (bangCount == 2) {
            exit(0); // Exit the program after 2 collisions
        }
        };

    // Create a clock to manage the time
    Clock clock;
    Time lastTime(clock.getElapsedTime());
    // Main loop to keep the window open
    while (window.isOpen()) {
        // Handle events like window closing
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Calculate the time since the last frame
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        // Update physics if there's a new frame
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        // Clear the window, draw the objects, and display them
        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(ceiling);
        window.draw(centerObstacle);
        window.display();
    }
}