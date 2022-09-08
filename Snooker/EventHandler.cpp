#include "EventHandler.h"

void EventHandler::check_events(sf::RenderWindow& app, PhysicsEngine &pe) {
    
    while (app.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            app.close();

        // catch the resize events
        if (event.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            app.setView(sf::View(visibleArea));
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i relative_position = sf::Mouse::getPosition(app);
                if (!pe.ball_selected()) {
                    for (Ball& b : pe.balls) {
                        if (b.point_is_inside(relative_position.x, relative_position.y)) {
                            pe.set_selected_ball(b);
                            break;
                        }
                    }
                }
               
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i relative_position = sf::Mouse::getPosition(app);
                if (pe.ball_selected()) {
                    float fx = (pe.selected_ball->x - relative_position.x) * 2000000.f;
                    float fy = (pe.selected_ball->y - relative_position.y) * 2000000.f;
                    pe.apply_force_to_ball(*pe.selected_ball, fx, fy);
                    pe.deselect_ball();
                }
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            if (pe.ball_selected()) {
                sf::Vector2i relative_position = sf::Mouse::getPosition(app);
                //pe.selected_ball->x = relative_position.x;
                //pe.selected_ball->y = relative_position.y;

                line_to_mouse[0] = sf::Vertex(sf::Vector2f(pe.selected_ball->x, pe.selected_ball->y));
                line_to_mouse[1] = sf::Vertex(sf::Vector2f(relative_position.x, relative_position.y));
    
            }
        }
    }
}