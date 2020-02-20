#ifndef __OPTIMIZER_H__
#define __OPTIMIZER_H__
#include "Matrix.h"
#include <time.h>
#include <vector>

using std::vector;

// All Optimizer has mini-batch

class Optimizer
{
private:
	string Optimizer_type;
	int numBatch;
	int BatchSize;
	vector<vector<int>> BatchSet;
public:
	// return : Update Matrix) update with Weight -= Output_Matirx_of_this_function

	Optimizer(string Name, int NB, int BS);

	Matrix Optimize();

	Matrix SGD(Matrix &Gradient);
	Matrix SGD(Matrix &Gradient, double momentum_rate); 
	Matrix Adagrad(Matrix &Graident, double Delta);
	Matrix RMSProp(Matrix &Gradient, double Delta, double Decay);
	Matrix Adam(Matrix &Gradient, double Delta, double Decay_F, double decay_S, int time);

};

vector<vector<int>> mini_batch_index_generator(int num_data, int batch_size);

#endif // !__OPTIMIZER_H__

#pragma once
