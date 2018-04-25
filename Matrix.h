#pragma once
#include <iostream>
#include <math.h>
#include "config.h"

class Matrix {

	//local variables
	int rows;
	int cols;
	float** matrix;

	//activation function
	float sigmoid(float x);
public:
	Matrix(int r, int c); //rows, colums

	//i dont use it..
	//but it works :D
	Matrix(Matrix& d);


	//multioplication (dot product)
	Matrix* dot(Matrix* n);

	//between -1,1
	void randomize();


	//Creates a single column array from the parameter array
	Matrix* singleColumnMatrixFromArray(float* arr, int l);

	//sets this matrix from an array
	void fromArray(float* arr, int l);
	

	//returns an array which represents this matrix
	float* toArray();

	//add one row of bias
	Matrix* addBias();

	//call activation function on matrix
	Matrix* activate();


	Matrix* removeBottomLayer();

	//mutate mutationrate*cols*rows elements
	void mutate(float mutationRate);

	//+18
	Matrix *crossover(Matrix& partner);

	//copying constructor another way ... With pointers :D
	Matrix* clone();

	~Matrix();

	friend std::ostream& operator<<(std::ostream& out, const Matrix& d);
	friend std::istream& operator>>(std::istream& in, Matrix& d);
};

