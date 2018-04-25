#pragma once
#include "Matrix.h"
#include <iostream>
#include <time.h>

class NeuralNet {

	int iNodes;//No. of input nodes
	int hNodes;//No. of hidden nodes
	int oNodes;//No. of output nodes

	Matrix* whi;//imput -> hidden
	Matrix* whh;//hidden -> hidden2
	Matrix* woh;//hidden2 -> output
#ifdef SAMESEED

#endif // SAMESEED

	unsigned int seed;
public:
	NeuralNet(int inputs, int hiddenNo, int outputNo);

	NeuralNet(NeuralNet& d);


	void mutate(float mr);

#ifndef SAMESEED
	unsigned int getSeed();
	void generateSeed();
#endif // !SAMESEED

	//the way brain thinks
	float* output(float* inputsArr, int l);

	//+18
	NeuralNet* crossover(NeuralNet* partner);

	//copy constructor with pointer
	NeuralNet* clone();

	~NeuralNet();

	friend std::ostream& operator<<(std::ostream& out, const NeuralNet& d);
	friend std::istream& operator>>(std::istream& in, NeuralNet& d);
};