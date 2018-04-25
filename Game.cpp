#include "Game.h"


Game::Game(NeuralNet* owner) : owner(owner)
{
}

double Game::startGame(status st, bool visibility)
{
	if (st == HUMAN)
	{
		//engine = new Engine();
		//while (engine->update());
		//int tmp = engine->endGame();
		//delete engine;
		//engine = nullptr;
		//return tmp;
		std::cout << "ERROR: Nie zaimplementowany Human Mode" << std::endl;
		return 0.0;
	}
	else
	{
#ifdef SAMESEED
		srand(2); //always sratr the same game 
#endif // SAMESEED
#ifndef SAMESEED
		if (visibility)
		{
			srand(owner->getSeed());
		}
		else
		{
			owner->generateSeed();
			srand(owner->getSeed());
		}
		
#endif // !SAMESEED

		

		aiengine = new AIEngine(visibility);
		//sf::sleep(sf::seconds(2)); <- usefull for manual playing
		float* s;
		s = new float[INPUTNODES]; //sensor vector
		bool* d;
		d = new bool[OUTPUTNODES]; //output vector - keyboard keys
		float* d_begin; //output in raw form
		d_begin = new float[OUTPUTNODES];
		for (int i = 1; i < INPUTNODES; i++)
			s[i] = 0; //first sensor informations
		s[0] = 1;
		do
		{

			delete d_begin;
			d_begin = owner->output(s, INPUTNODES); //gain next move
			for (int i = 0; i < OUTPUTNODES; i++)
				if (d_begin[i] > 0.7) //convert float to bool
					d[i] = 1;
				else
					d[i] = 0;
			delete s;
			s=aiengine->update(d);  //gain new sensor vector
		} while (s[0]<100); //s[0]>=100 == game is lost
		double tmp = aiengine->endGame(); //get score
		delete aiengine;
		aiengine = nullptr;
		return tmp;
	}
	
}

Game::~Game()
{
	//if (engine) delete engine; 
	if (aiengine) delete aiengine; 
}
