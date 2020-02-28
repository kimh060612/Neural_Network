#include "ConvNet.h"

Conv2DNet::Conv2DNet()
{
}

Conv2DNet::~Conv2DNet()
{
}

void Conv2DNet::set_Input(int *size)
{
	this->Model.push_back(INPUT);
	Tensor input(size[0], size[1], size[2], size[3]);
	Tensor delta(size[0], size[1], size[2], size[3]);

	this->FeatrueMap.push_back(input);
	this->DeltaMap.push_back(delta);

}

void Conv2DNet::Put_Conv2DNet(int *size,int stride, int Padding)
{
	this->Model.push_back(CONV2D);


}

void Conv2DNet::Put_Pooling(int *size, int stride, int Padding)
{
	this->Model.push_back(POOLING);
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
