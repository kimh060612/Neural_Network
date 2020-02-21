#ifndef __NEURALNET_H__
#define __NEURALNET_H__

#include "Matrix.h"
//#include "Optimizer.h"
#include <string>
#include <time.h>
#include <vector>

using std::vector;

class NeuralNet
{
private:
	int Layer_num;
	int *Node_num;
	Matrix *Node;
	Matrix *Weight;
	Matrix *Delta;
	Matrix *Bias;
	double Learning_rate;
	string Act_name;

public:

	NeuralNet(int Layer_num, int* Node_num, double Learning_rate, string Act_); // Optimizer type: Default: Normal
	~NeuralNet();

	void Initialize_Weight();
	int Feed_forward(Matrix *input);
	void Calc_Delta(Matrix *target);
	void Update_Weight(); // Input: Optimizer Object
	int Train(Matrix *Input, Matrix *Output);

	void SGD(Matrix *Input, Matrix *Output,int NumData, int BatchSize, int total_epoch);
	void SGD(Matrix &Gradient, double momentum_rate);
	void Adagrad(Matrix &Graident, double Delta);
	void RMSProp(Matrix &Gradient, double Delta, double Decay);
	void Adam(Matrix &Gradient, double Delta, double Decay_F, double decay_S, int time);

};

class Act_Func
{
public:
	// Feed forward Activation Func.
	double Sigmoid(double x)
	{
		return 1. / (1. + exp(-x));
	}
	double Tanh(double x)
	{
		return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
	}
	double ReLU(double x)
	{
		return x > 0 ? x : 0;
	}
	double Identity(double x)
	{
		return x;
	}
	double *Softmax(double *OUT)
	{
		int N = sizeof(OUT) / sizeof(double);
		double *Pr = new double[N];
		double sum = 0;
		for (int i = 0; i < N; i++)
		{
			sum += OUT[i];
		}
		for (int i = 0; i < N; i++)
		{
			Pr[i] = OUT[i] / sum;
		}
		return Pr;
	}
	// Derivative of Activation Func.
	double De_Sigmoid(double x)
	{
		double tmp = Sigmoid(x);
		return tmp * (1. - tmp);
	}
	double De_tanh(double x)
	{
		double tmp = Tanh(x);
		return 1. - tmp * tmp;
	}
	double De_ReLU(double x)
	{
		return x > 0 ? 1. : 0;
	}
	double De_Identity(double x)
	{
		return 1.;
	}

	string name;

	Act_Func(string Name)
	{
		this->name = Name;
	}

	double Forward_Func(double x)
	{
		if (this->name == "Sigmoid")return this->Sigmoid(x);
		else if (this->name == "Tanh")return this->Tanh(x);
		else if (this->name == "ReLU")return this->ReLU(x);
		else if (this->name == "Identity")return this->Identity(x);
	}
	double *Forward_vector_Function(double *X)
	{
		if (this->name == "Softmax")return this->Softmax(X);
	}

	double Backward_Func(double x)
	{
		if (this->name == "Sigmoid")return this->De_Sigmoid(x);
		else if (this->name == "Tanh")return this->De_tanh(x);
		else if (this->name == "ReLU")return this->De_ReLU(x);
		else if (this->name == "Identity")return this->De_Identity(x);
	}

};

void One_Hot_Encoding(int Data_Num, int *target, int num_class, Matrix *OneHot);
vector<vector<int>> mini_batch_index_generator(int num_data, int batch_size);

#endif // !__NEURALNET_H__

#pragma once
