#ifndef __ACTTIVATION_H__
#define __ACTTIVATION_H__

#include <cmath>
#include "Matrix.h"
#include <string>

using std::string;

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

Matrix Feed_Function(Matrix U, Act_Func F);
Matrix Backward_Function(Matrix U, Act_Func De);

#endif // !__ACTTIVATION_H__


#pragma once
