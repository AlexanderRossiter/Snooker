#pragma once
#include "PhysicsEngine.h"

void rack_balls(PhysicsEngine& pe) {
	float ball_radius = 5.0f;
	// Yellow
	pe.add_ball(250, 625, ball_radius);
	pe.balls.back().set_colour(sf::Color::Yellow);

	// Green
	pe.add_ball(150, 625, ball_radius);
	pe.balls.back().set_colour(sf::Color(0,117,0));

	// Brown
	pe.add_ball(200, 625, ball_radius);
	pe.balls.back().set_colour(sf::Color(117, 70, 4));

	// Blue
	pe.add_ball(200, 400, ball_radius);
	pe.balls.back().set_colour(sf::Color::Blue);

	// Pink
	pe.add_ball(200, 200, ball_radius);
	pe.balls.back().set_colour(sf::Color(240,26,129));

	// Black
	pe.add_ball(200, 75, ball_radius);
	pe.balls.back().set_colour(sf::Color::Black);

	// Reds
	float ball_radius_offset = ball_radius + 0.2f;
	float delta_h = 2.f * ball_radius_offset * 0.86602540378; // sin(60)
	int start_x = 200;
	int start_y = 190;
	// First row
	pe.add_ball(start_x, start_y, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	// Second row
	pe.add_ball(start_x - ball_radius_offset, start_y -delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x + ball_radius_offset, start_y -delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	// Third row
	pe.add_ball(start_x - 2.f* ball_radius_offset, start_y - 2.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x, start_y - 2.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x + 2.f* ball_radius_offset, start_y - 2.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	// Fourth row
	pe.add_ball(start_x - 3.f * ball_radius_offset, start_y - 3.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x- ball_radius_offset, start_y - 3.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x + ball_radius_offset, start_y - 3.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x + 3.f * ball_radius_offset, start_y - 3.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	// Fifth row
	pe.add_ball(start_x - 4.f * ball_radius_offset, start_y - 4.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x - 2.f* ball_radius_offset, start_y - 4.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x, start_y - 4.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x + 2.f * ball_radius_offset, start_y - 4.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);
	pe.add_ball(start_x + 4.f * ball_radius_offset, start_y - 4.f * delta_h, ball_radius);
	pe.balls.back().set_colour(sf::Color::Red);

	// Cue ball
	pe.add_ball(170, 625, ball_radius);
	pe.balls.back().set_colour(sf::Color::White);

}