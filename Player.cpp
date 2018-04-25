#include "Player.h"

sf::RectangleShape * Player::createSquare(sf::Vector2f position)
{
	sf::RectangleShape* tmp = new sf::RectangleShape(sf::Vector2f(SQUARESIZE, SQUARESIZE));
	tmp->setFillColor(sf::Color::White);
	tmp->setOrigin(SQUARESIZE /2, SQUARESIZE /2);
	tmp->move(position);
	return tmp;
}

Player::Player(sf::Vector2f position)
{
	head = createSquare(position);
	for (int i = 0; i < 2; i++)
		body.push_back( createSquare( position + sf::Vector2f(0, -(i+1)*SQUARESIZE) ) );
	size = body.size()+1;
	direction = 0;
}

Player::~Player()
{
	for (int i = 0; i < size - 1; i++)
		delete body[i];
	body.clear();
	delete head;
	size = 0;
}

bool Player::update()
{
	if (body.empty())
	{
		//std::cout << "ERROR: empty snake (Player::update)" << std::endl;
		return 0;
	}
	sf::RectangleShape* tmp = body[size-2];
	body.pop_back();
	tmp->setPosition(head->getPosition());
	body.insert( body.begin(),tmp);
	switch (direction)
	{
	case 0:
		head->move(0, SQUARESIZE);
		break;
	case 2:
		head->move(SQUARESIZE,0);
		break;
	case 4:
		head->move(0, -SQUARESIZE);
		break;
	case 6:
		head->move(-SQUARESIZE, 0);
		break;
	}
	for (int i = 0; i < size - 1; i++)
		if (head->getPosition() == body[i]->getPosition())    //if he tries to eat himself
			return 0;
	return 1;
}

void Player::turn(int dir)
{
	if (dir == 2)
	{
		direction+=2;
		if (direction == 8)
			direction = 0;
	}
	else
	{
		direction-=2;
		if (direction == -2)
			direction = 6;
	}

}

void Player::setRotation(int dir)
{
	direction = dir;
}

sf::Vector2f Player::getPosition()
{
	return head->getPosition();
}

int Player::getRotation()
{
	return direction;
}

bool Player::bodyContains(sf::Vector2f xy)
{
	for (int i = 0; i < size - 1; i++)
	{
		if (body[i]->getPosition() == xy)
		{
			return 1;
		}
		if (getPosition() == xy)
			return 1;
	}
	return 0;
}

void Player::grow()
{
	body.push_back( createSquare( body[size-2]->getPosition() ) );
	size++;
}

int Player::points()
{
	return size;
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*head);
	for (int i = 0; i < size - 1; i++)
		target.draw(*body[i]);
}
