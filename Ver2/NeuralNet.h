#ifndef __NEURALNET_H__
#define __NEURALNET_H__

#include "ActivationFunction.h"
#include <time.h>
#include <vector>


using std::vector;

class NeuralNet
{
protected:
	int Layer_num;
	int *Node_num;
	Matrix *Node;
	Matrix *Weight;
	Matrix *Delta;
	Matrix *Bias;
	double Learning_rate;
	string Act_name;

public:

	NeuralNet(int Layer_num, int* Node_num, double Learning_rate, string Act_);
	~NeuralNet();

	void Initialize_Weight();
	int Feed_forward(Matrix *input);
	void Calc_Delta(Matrix *target);
	void Update_Weight(); // Input: Optimizer Object
	int Train(Matrix *Input, Matrix *Output);
	void TestModel(Matrix *TestInput, Matrix *TestOutput);// 일단 CNN 짜고 하자

	void SGD(Matrix *Input, Matrix *Output, int NumData, int BatchSize, int total_epoch);
	void SGD(Matrix &Gradient, double momentum_rate);
	void Adagrad(Matrix &Graident, double Delta);
	void RMSProp(Matrix &Gradient, double Delta, double Decay);
	void Adam(Matrix &Gradient, double Delta, double Decay_F, double decay_S, int time);

};

void One_Hot_Encoding(int Data_Num, int *target, int num_class, Matrix *OneHot);
vector<vector<int>> mini_batch_index_generator(int num_data, int batch_size);

#endif // !__NEURALNET_H__

#pragma once
