#include <iostream>
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include "Ball.h"
#include "setup.h"


const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    sf::RenderWindow app(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Snooker");

    sf::Clock clock;
    float left_over_time = 0;

    PhysicsEngine pe;

    rack_balls(pe);

    pe.set_extents(10, SCR_WIDTH-10, 10, SCR_HEIGHT-10);

    sf::Texture texture;
    if (!texture.loadFromFile("./Resources/snooker_table.png"))
    {
        std::cout << "Failed to load texture.\n";
        return -1;
    }
    sf::Sprite background;
    background.setTexture(texture);
    // Main loop.
    while (app.isOpen())
    {

        // Events
        EventHandler eventHandler;
        eventHandler.check_events(app, pe);

        // Time keeping
        sf::Time elapsed_time = clock.getElapsedTime();
        clock.restart();
        float elapsed_time_sec = elapsed_time.asSeconds();
        int n = (elapsed_time_sec + left_over_time) / pe.delta_t;
        left_over_time = elapsed_time_sec - n * pe.delta_t;
        float fps = 1.0f / elapsed_time_sec;

        
        app.clear();
        app.draw(background);

        // The Physics steps
        for (int nstep = 0; nstep < n; nstep++) {
            pe.update();
        }
        pe.display(app);
        app.display();
    }

	return 0;
}