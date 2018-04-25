#include "AIEngine.h"



void AIEngine::generateMeal()
{
	bool hit;
	int x, y;
	do
	{

		hit = 0;
		x = (rand() % (WINDOWX / SQUARESIZE - 2)) * SQUARESIZE + SQUARESIZE;// +SQUARESIZE / 2;
		y = (rand() % (WINDOWY / SQUARESIZE - 2)) * SQUARESIZE + SQUARESIZE;// +SQUARESIZE / 2;
		if ( snake->bodyContains( sf::Vector2f(x, y) ) )
			hit = 1;
		if (!inside(sf::Vector2f(x, y)))
			hit = 1;

	} while (hit);
	fruit.setPosition(sf::Vector2f(x, y));
}

bool AIEngine::inside(sf::Vector2f xy)
{
	if (xy.x <= SQUARESIZE/2 || xy.x >= WINDOWX - SQUARESIZE/2 || xy.y <= SQUARESIZE/2 || xy.y >= WINDOWY - SQUARESIZE/2)
		return false;
	return true;
}


float AIEngine::sensorFunction(float distance)
{
	return 1.0 / distance;
	//return 1.0 - 1.0 / (1.0 + exp(-(distance - 5.0) / 1.0));
}

float* AIEngine::LookAt(int direction)
{
	sf::Vector2f position = snake->getPosition();
	
	sf::Vector2f step;
	float distance = 0;
	switch (direction)
	{
	case 0:
		step = sf::Vector2f(0, SQUARESIZE);
		break;
	case 1:
		step = sf::Vector2f(SQUARESIZE, SQUARESIZE);
		break;
	case 2:
		step = sf::Vector2f(SQUARESIZE, 0);
		break;
	case 3:
		step = sf::Vector2f(SQUARESIZE, -SQUARESIZE);
		break;
	case 4:
		step = sf::Vector2f(0, -SQUARESIZE);
		break;
	case 5:
		step = sf::Vector2f(-SQUARESIZE, -SQUARESIZE);
		break;
	case 6:
		step = sf::Vector2f(-SQUARESIZE, 0);
		break;
	case 7:
		step = sf::Vector2f(-SQUARESIZE, SQUARESIZE);
		break;
	default:
		std::cout << "ERROR: bad view direction" << std::endl;
		return nullptr;
	}

	bool s = 1;
	bool f = 1;
	bool w = 1;
	float* view = new float[3]; //s,f,w
	while (s || f || w)
	{
		position += step;
		distance++;
		if ( f && position == fruit.getPosition() )
		{
			f = 0;
			view[1] = 1;
		}
		if (s && snake->bodyContains(position))
		{
			s = 0;
			view[0] = sensorFunction(distance);
		}
		if (!inside(position))
		{
			if(s)
				view[0] = 0;
			if(f)
				view[1] = 0;
			view[2] = sensorFunction(distance);
			return view;
		}
			
	}

}

AIEngine::AIEngine(bool visibility) :visibility(visibility)
{
	if (visibility)
	{
		clock.restart();
		thisFrame = lastFrame = clock.getElapsedTime();
	}
	if (visibility)
		window.create(sf::VideoMode(WINDOWX, WINDOWY), "Asteroids");

	lifetime = lifespan = 0;
	snake = new Player(sf::Vector2f(((WINDOWX / SQUARESIZE)/2)*SQUARESIZE, ((WINDOWY / SQUARESIZE) / 2)*SQUARESIZE));

	fruit.setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
	fruit.setFillColor(sf::Color::Red);
	fruit.setOrigin(SQUARESIZE / 2, SQUARESIZE / 2);
	generateMeal();

	lines = new sf::Vertex[8];
	lines[7] = lines[0] = sf::Vertex(sf::Vector2f(SQUARESIZE/2, SQUARESIZE/2));
	lines[2] = lines[1] = sf::Vertex(sf::Vector2f(SQUARESIZE/2, WINDOWY - SQUARESIZE/2));
	lines[4] = lines[3] = sf::Vertex(sf::Vector2f(WINDOWX - SQUARESIZE/2, WINDOWY - SQUARESIZE/2));
	lines[6] = lines[5] = sf::Vertex(sf::Vector2f(WINDOWX - SQUARESIZE/2, SQUARESIZE/2));
}

float * AIEngine::update(bool *keyboard)
{
	// UPDATE TIME
	
	if (visibility)
	{
		/*
		lastFrame = thisFrame;

		thisFrame = clock.getElapsedTime();
		//delta = thisFrame.asSeconds() - lastFrame.asSeconds();
		if (lastFrame - thisFrame>sf::seconds(DELTATIME))
			sf::sleep(sf::seconds(DELTATIME) - thisFrame + lastFrame);
		thisFrame = clock.getElapsedTime();
		*/
		sf::sleep(sf::seconds(DELTATIME));
		lifespan += DELTATIME;
		lifetime += DELTATIME;
	}
	else
	{
		//thisFrame = thisFrame + sf::seconds(DELTATIME);
		lifespan += DELTATIME;
		lifetime += DELTATIME;
	}
	if(lifespan>20)
	{
		if (visibility)
			std::cout << "Die from starvation" << std::endl;
		float* smierc = new float[1];  //die from starvation, probably loop
		smierc[0] = 200;
		return smierc;
	}

	//STEERING
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		//if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A)
		//	snake->turn(2);
		//if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D)
		//	snake->turn(4);
	};
	if (keyboard[0])
	{
		//snake->turn(2);
		snake->setRotation(0);
	}
	else if (keyboard[1])
	{
		//snake->turn(4);
		snake->setRotation(2);
	}
	else if (keyboard[2])
	{
		snake->setRotation(4);
	}
	else if (keyboard[3])
	{
		snake->setRotation(6);
	}
	
	//UPDATE ENTITIES
	if (!snake->update())
	{
		if (visibility)
			std::cout << "Die from self-eating" << std::endl;
		float* smierc = new float[1];
		smierc[0] = 200;
		return smierc;
	}
	if (snake->getPosition() == fruit.getPosition())
	{
		snake->grow();
		generateMeal();
		lifespan = 0;
	}
	if(!inside(snake->getPosition()))
	{
		if(visibility)
			std::cout << "Die from headbutting the wall" << std::endl;
		float* smierc = new float[1];
		smierc[0] = 200;
		return smierc;
	}

	//VISUALIZATION
	if (visibility)
	{
		window.clear(sf::Color::Black);
		window.draw(*snake);
		window.draw(fruit);
		window.draw(lines, 8, sf::Lines);
		window.display();
	}


	//everything is fine
	//i live
	
	float* sences = new float[INPUTNODES];
	for (int i = 0; i < 8; i++)
	{
		float* view = LookAt(i);
		for (int j = 0; j < 3; j++)
			sences[i * 3 + j] = view[j];
		delete[] view;
	}
	
	//if (visibility)
	//	for(int i=0;i<8;i++)
	//		std::cout << sences[i*3+1] <<  std::endl;
	//float* sences = new float[INPUTNODES];
	//for (int i = 0; i < INPUTNODES; i++)
	//	sences[i] = 0;
	return sences;
}

double AIEngine::endGame()
{
	//std::cout << "ENd game";
	if (lifetime > 30)
		lifetime = 30;
	if (visibility)
		window.close();
	if (visibility)
		std::cout << "Live score: " << lifetime * lifetime*(pow(2, snake->points())) << std::endl;
	return lifetime*lifetime*(pow(2,snake->points()));
}

AIEngine::~AIEngine()
{
	delete snake;
	delete[] lines;
}
