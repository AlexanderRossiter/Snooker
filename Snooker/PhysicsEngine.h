#pragma once

#include <vector>
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>


class PhysicsEngine
{
public:
	std::vector<Ball> balls;
	void set_selected_ball(Ball& ball);
	void deselect_ball();
	void update();
	void add_ball(float x, float y, float r);
	void display(sf::RenderWindow& app);
	bool ball_selected();
	Ball get_selected_ball();
	Ball* selected_ball = nullptr;
	void set_extents(float _xmin, float _xmax, float _ymin, float _ymax);
	void apply_force_to_ball(Ball& b, float fx, float fy);

	float delta_t = 0.0001;



private:
	void calculate_static_collisions();
	void calculate_dynamic_collisions();
	void calculate_wall_collisions();
	void integrate_accelerations();
	bool balls_collided(Ball& b1, Ball& b2);
	bool x_value_in_ball(Ball& b, float xv);
	bool y_value_in_ball(Ball& b, float yv);
	std::vector<std::vector<Ball*>> colliding_pairs;

	int xmin;
	int xmax;
	int ymin;
	int ymax;
};

