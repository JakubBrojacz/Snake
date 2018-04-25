#include "config.h"

double GaussRandom()
{
	static std::default_random_engine engine;
	static std::normal_distribution<double> distribution(0.0, 1.0);
	return distribution(engine);
}
