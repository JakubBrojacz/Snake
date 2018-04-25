#include "Object.h"
#include <iostream>

Object::Object()
{
	std::cout << "ERROR: empty constructor of class Object" << std::endl; //I said to not use this
}


Object::Object(int a, int b, int c)
{
	brain = new NeuralNet(a, b, c);
	gra = new Game(brain);
}

Object::Object(const Object &d)
{
	brain = d.brain->clone();
	gra = new Game(brain);
}

void Object::mutate(float mutationRate)
{
	brain->mutate(mutationRate);
}

double Object::graj(bool visibility)
{
	return gra->startGame(AI,visibility);
}

Object* Object::crossover(Object* d)
{
	Object *ne = new Object(*this);
	delete ne->brain;
	delete ne->gra;
	ne->brain = brain->crossover(d->brain);
	ne->gra = new Game(ne->brain);
	return ne;
}



Object::~Object()
{
	delete brain;
	delete gra;
}

std::ostream & operator<<(std::ostream & out, const Object & z)
{
	out << *(z.brain);
	return out;
}

std::istream & operator>>(std::istream & in, Object & z)
{
	in >> *(z.brain);
	return in;
}
