#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsEngine.h"
#include <iostream>

class EventHandler
{
public:
	sf::RectangleShape line;
	void check_events(sf::RenderWindow& app, PhysicsEngine& pe);


private:
	sf::Event event;

};

