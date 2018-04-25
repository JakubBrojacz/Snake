#pragma once

#include "Game.h"
#include "NeuralNet.h"
#include <iostream>


class Game;

class Object
{
private:
	NeuralNet * brain;
	Game* gra;
public:
	//almost never use it
	Object();
	
	//input neurons, hidden neruons, output nerons
	Object(int, int, int);
	Object(const Object&);

	//mutationRate from [0;1]
	void mutate(float mutationRate);

	//makes AI play the game. Parametr tells if it should be visible, or only make score
	double graj(bool = 0);

	//use in mutations
	Object* crossover(Object* d);

	friend std::ostream& operator<<(std::ostream& out, const Object& z);
	friend std::istream& operator>>(std::istream& in, Object& z);

	~Object();
};