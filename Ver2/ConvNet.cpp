#include "ConvNet.h"

Conv2DNet::Conv2DNet()
{
}

Conv2DNet::~Conv2DNet()
{
}

void Conv2DNet::set_Input(int *size)
{
	this->Num_Data = size[0];
	this->Model.push_back(INPUT);
	Tensor input(size[1], size[2], size[3]);
	Tensor delta(size[1], size[2], size[3]);

	this->FeatrueMap.push_back(input);
	this->DeltaMap.push_back(delta);
	this->LayerNumCONVNET++;
}

void Conv2DNet::Put_Conv2DNet(int *size,int stride, int Padding)
{
	this->Model.push_back(CONV2D);
	Tensor Weight(size[0], size[1], size[2], size[3]);

	this->WeightFilter.push_back(Weight);

	this->Stride_Padding_CONV.push_back(make_pair(stride, Padding));
	this->LayerNumCONVNET++;
}

void Conv2DNet::Put_Pooling(int *size, int stride, int Padding)
{
	this->Model.push_back(POOLING);
	Tensor Pooling(size[0], size[1], size[2], size[3]);

	this->PoolingFilter.push_back(Pooling);
	this->Stride_Padding_Pooling.push_back(make_pair(stride, Padding));

}

void Conv2DNet::put_FCNN(int Layer_num, int* Node_num, double Learning_rate, string Act_)
{
	this->Model.push_back(FCNN);
}

void Conv2DNet::Forward()
{
}

void Conv2DNet::Calc_Delta()
{
}

void Conv2DNet::Backward()
{
}

void Conv2DNet::Train()
{
}

Matrix Flatten(Tensor & Map)
{
	return Matrix();
}

pair<int, int> OutSize(int H, int W, int strideH, int strideW, int Padding)
{
	
}