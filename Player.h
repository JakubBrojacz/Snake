#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "config.h"

class AIEngine;

class Player : public sf::Drawable
{
	std::vector < sf::RectangleShape* > body;
	int size;
	sf::RectangleShape* head;

	int direction; //0 - up, 2 - right, 4 - down, 6 - left 

	sf::RectangleShape* createSquare(sf::Vector2f position);
public:
	Player(sf::Vector2f position);
	~Player();

	bool update();
	void turn(int dir); //2 - right, 4 - left
	void setRotation(int dir);
	void grow();

	sf::Vector2f getPosition();
	int getRotation(); //0 - up, 2 - right, 4 - down, 6 - left 
	bool bodyContains(sf::Vector2f);

	int points();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};