#ifndef __OPTIMIZER_H__
#define __OPTIMIZER_H__

#include "Matrix.h"
#include <string>
#include <vector>
#define Normal_ 0
#define SGD_ 1
#define SGDNestrovMomentum_ 2
#define Adam_ 3
#define Adagrad_ 4
#define RMSProp_ 5

using std::string;
using std::vector;

class Optimizer
{
private:
	int Type_Optimizer;
public:
	Optimizer(string Name);

	void SGD(Matrix *Input, Matrix *Output, int NumData, int BatchSize, int total_epoch);
	void SGD(Matrix *Input, Matrix *Output, double momentum_rate);
	void Adagrad(Matrix *Input, Matrix *Output, double Delta);
	void RMSProp(Matrix *Input, Matrix *Output, double Delta, double Decay);
	void Adam(Matrix *Input, Matrix *Output, double Delta, double Decay_F, double decay_S, int time);

};

vector<vector<int>> mini_batch_index_generator(int num_data, int batch_size);

#endif // !__OPTIMIZER_H__
#pragma once
