#pragma once

#include "Object.h"
#include <vector>
#include <fstream>

class Generation
{
private:
	std::vector < Object* > gen; //all objects in current generation
	std::vector < double > wyn; //their score
	int num; //number of objects
	float mutationRate; //from [0;1]
	Object* ChooseObject(); //choose random object (object with hier score has better chanse

	void sort(); //sort gen based on wyn
public:
	//choose number of generated objects
	Generation(int = 100);

	//make everyone play and test their skills (update wyn)
	void play();

	//mutate everyone based on wyn (better play() first)
	void nextGen();

	void doubleMutationRate();
	void halveMutationRate();

	//get index of best object
	int maks(); 

	//get score of given index
	double score(int);

	//make object play, so we can see it (parametr - index of object)
	void visual(int = 0);

	void save(std::string file);
	void load(std::string file);
};