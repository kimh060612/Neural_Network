#ifndef __CONVNET_H__
#define __CONVNET_H__
#include "Tensor.h"
#include "NeuralNet.h"
#include <vector>

#define INPUT 0
#define CONV2D 1
#define POOLING 2
#define FCNN 3

using std::vector;

class Conv2DNet : private NeuralNet
{
private:

	vector<Tensor> FeatrueMap;
	vector<Tensor> DeltaMap;
	vector<Tensor> WeightFilter;
	vector<Tensor> PoolingFilter;
	vector<Matrix> Bias;
	vector<pair<int, int>> Stride_Padding_CONV;
	vector<pair<int, int>> Stride_Padding_Pooling;
	vector<int> Model;
	
	int Num_Data;
	int LayerNumCONVNET = 0;
	int Learing_rate;

public:

	Conv2DNet();
	~Conv2DNet();

	void set_Input(int *size);	// Input image size setting. 4D image will be input. [N, H, W, D]
	void Put_Conv2DNet(int *size, int stride, int Padding); // CONV2D input will be 4D [N, H, W, D]
	void Put_Pooling(int *size, int stride, int Padding); // POOLING input will be 4D [N, H, W, D] ([1,H,W,1] is Recommended)
	void put_FCNN(int Layer_num, int* Node_num, double Learning_rate, string Act_);

	void Forward();
	void Calc_Delta();
	void Backward(); // Update & Gradient Descent Optimizer Needed!

	void Train();

};

Matrix Flatten(Tensor &Map);

#endif // !__CONVNET_H__
#pragma once
