#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include "config.h"
#include "Player.h"


class AIEngine
{
protected:
	double points;
	double lifespan;
	double lifetime;


	sf::Time lastFrame;
	sf::Time thisFrame;
	sf::Clock clock;
	sf::RenderWindow window;
	bool visibility;

	Player* snake;
	sf::RectangleShape fruit;
	sf::Vertex* lines;

	void generateMeal();
	bool inside(sf::Vector2f);

	float sensorFunction(float distance);
	float* LookAt(int direction); // for AI sensor //1 - himself, 2 - fruit, 3 - wall
	//float sensorFunction(float distance);
public:

	AIEngine(bool visibility = 1); //visibility, refreshing rate
	float* update(bool*);
	double endGame();

	~AIEngine();
};