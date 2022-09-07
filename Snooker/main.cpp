#include <iostream>
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include "Ball.h"


const unsigned int SCR_WIDTH = 400;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    sf::RenderWindow app(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "Snooker");

    sf::Clock clock;
    float left_over_time = 0;

    PhysicsEngine pe;

    for (int i = 0; i < 10; i++) {
        pe.add_ball(std::rand() % SCR_WIDTH, std::rand() % SCR_HEIGHT, 5.0f);
    }

    pe.set_extents(0, SCR_WIDTH, 0, SCR_HEIGHT);

    sf::Texture texture;
    if (!texture.loadFromFile("./Resources/snooker_table.png"))
    {
        std::cout << "Failed to load texture.\n";
        return -1;
    }
    sf::Sprite background;
    background.setTexture(texture);
    background.setScale(0.5f, 0.5f);
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

        
        //std::cout << n << std::endl;

        app.clear();
        // The Physics steps
        app.draw(background);
        for (int nstep = 0; nstep < n; nstep++) {
            pe.update();
        }
        pe.display(app);
        if (pe.ball_selected()) {
            app.draw(eventHandler.line_to_mouse, 2, sf::Lines);
        }
        app.display();
    }

	return 0;
}