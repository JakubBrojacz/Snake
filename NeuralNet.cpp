#include "NeuralNet.h"

NeuralNet::NeuralNet(int inputs, int hiddenNo, int outputNo) :iNodes(inputs), oNodes(outputNo), hNodes(hiddenNo)
{
	//creating Matrix
	whi = new Matrix(hNodes, iNodes + 1);
	whh = new Matrix(hNodes, hNodes + 1);
	woh = new Matrix(oNodes, hNodes + 1);

	//randomize
	whi->randomize();
	whh->randomize();
	woh->randomize();
}

NeuralNet::NeuralNet(NeuralNet & d) : iNodes(d.iNodes), hNodes(d.hNodes), oNodes(d.oNodes)
{
	//copy matrix constructor
	whi = d.whi->clone();
	whh = d.whh->clone();
	woh = d.woh->clone();
}

void NeuralNet::mutate(float mr)
{
	//mutates each matrix
	whi->mutate(mr);
	whh->mutate(mr);
	woh->mutate(mr);
}

#ifndef SAMESEED
unsigned int NeuralNet::getSeed()
{
	return seed;
}
void NeuralNet::generateSeed()
{
	seed = time(NULL);
}
#endif // !SAMESEED



float * NeuralNet::output(float * inputsArr, int l)
{

	//i found this on net :-P
	Matrix* inputs = woh->singleColumnMatrixFromArray(inputsArr, l);

	//add bias 
	Matrix* inputsBias = inputs->addBias();


	//calculate first layer of hidden
	Matrix* hiddenInputs = whi->dot(inputsBias);

	//activation function
	Matrix* hiddenOutputs = hiddenInputs->activate();

	//add bias
	Matrix* hiddenOutputsBias = hiddenOutputs->addBias();

	//calculate second layer
	Matrix* hiddenInputs2 = whh->dot(hiddenOutputsBias);
	Matrix* hiddenOutputs2 = hiddenInputs2->activate();
	Matrix* hiddenOutputsBias2 = hiddenOutputs2->addBias();

	//output
	Matrix* outputInputs = woh->dot(hiddenOutputsBias2);
	Matrix* outputs = outputInputs->activate();

	float* wyn = (*outputs).toArray();

	//cleaning
	delete inputs;
	delete inputsBias;
	delete hiddenInputs;
	delete hiddenOutputs;
	delete hiddenOutputsBias;
	delete hiddenInputs2;
	delete hiddenOutputs2;
	delete hiddenOutputsBias2;
	delete outputInputs;
	delete outputs;

	return wyn;
}

NeuralNet * NeuralNet::crossover(NeuralNet * partner)
{

	//creates a new child from crossover of every matrix
	NeuralNet* child = new NeuralNet(iNodes, hNodes, oNodes);
	delete child->whi;
	delete child->whh;
	delete child->woh;
	child->whi = whi->crossover(*partner->whi);
	child->whh = whh->crossover(*partner->whh);
	child->woh = woh->crossover(*partner->woh);
	return child;
}

NeuralNet * NeuralNet::clone()
{
	NeuralNet* clone = new NeuralNet(iNodes, hNodes, oNodes);
	clone->whi = whi->clone();
	clone->whh = whh->clone();
	clone->woh = woh->clone();

	return clone;
}

NeuralNet::~NeuralNet()
{
	delete whi;
	delete whh;
	delete woh;
}

std::ostream & operator<<(std::ostream & out,const NeuralNet& d)
{
	out << d.iNodes << " " << d.hNodes << " " << d.oNodes << std::endl;
	out << *(d.whi) << std::endl << *(d.whh) << std::endl << *(d.woh) << std::endl;
	return out;
}

std::istream & operator>>(std::istream & in, NeuralNet & d)
{
	in >> d.iNodes;
	in >> d.hNodes;
	in >> d.oNodes;

	in >> *(d.whi);
	in >> *(d.whh);
	in >> *(d.woh);
	return in;
}
