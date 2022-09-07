#pragma once

#include <SFML/graphics.hpp>
class Ball
{
public:
	Ball(float x, float y, float r) : x(x), y(y), r(r) { sf_shape.setRadius(r); sf_shape.setOrigin(r, r); mass = r * r; }
	~Ball() {};

	float x, y, vx=0, vy=0, ax=0, ay=0;
	float r;
	float mass;
	int id;

	sf::CircleShape sf_shape;

	bool point_is_inside(float x, float y);
	void draw(sf::RenderWindow& app);
	void set_colour(sf::Color c);
};

