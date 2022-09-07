#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsEngine.h"
#include <iostream>

class EventHandler
{
public:
	sf::Vertex line_to_mouse[2];
	void check_events(sf::RenderWindow& app, PhysicsEngine& pe);


private:
	sf::Event event;

};

