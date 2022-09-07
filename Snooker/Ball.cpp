#include "Ball.h"

void Ball::draw(sf::RenderWindow &app) {
	sf_shape.setPosition(x, y);
	app.draw(sf_shape);
}

bool Ball::point_is_inside(float xp, float yp) {
	return std::sqrt((xp - x) * (xp - x) + (yp - y) * (yp - y)) < r;
}

void Ball::set_colour(sf::Color c) {
	sf_shape.setFillColor(c);
}