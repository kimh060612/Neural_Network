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
}

void Conv2DNet::Put_Conv2DNet(int *size,int* stride, int* Padding)
{
	this->Model.push_back(CONV2D);
	int n = this->FeatrueMap.size();
	int inH = this->FeatrueMap[n - 1].Height;
	int inW = this->FeatrueMap[n - 1].Width;
	Tensor Weight(size[0], size[1], size[2], size[3]);
	pair<int, int> OutS = OutSize(inH, inW, stride[0], stride[1], Padding[0], Padding[0], size[1], size[2]);
	Tensor OUTMAP(OutS.first,OutS.second, size[3]);

	this->WeightFilter.push_back(Weight);
	this->FeatrueMap.push_back(OUTMAP);
	this->Stride_Padding_CONV.push_back(make_pair(stride, Padding));
}

void Conv2DNet::Put_Pooling(int *size, int* stride, int* Padding)
{
	this->Model.push_back(POOLING);
	int n = this->FeatrueMap.size();
	int inH = this->FeatrueMap[n - 1].Height;
	int inW = this->FeatrueMap[n - 1].Width;
	pair<int, int> OutS = OutSize(inH, inW, stride[0], stride[1], Padding[0], Padding[0], size[1], size[2]);
	Tensor OUTMAP(OutS.first, OutS.second, size[3]); // size[3] will alomost be 1

	this->PoolingFilter.push_back(size);
	this->Stride_Padding_Pooling.push_back(make_pair(stride, Padding));
	this->FeatrueMap.push_back(OUTMAP);
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

pair<int, int> OutSize(int H, int W, int strideH, int strideW, int PaddingH, int PaddingW, int FilterH, int FilterW)
{
	int outH = ((H - FilterH + 2*PaddingH) / strideH) + 1;
	int outW = ((W - FilterW + 2 * PaddingH) / strideW) + 1;
	return make_pair(outH, outW);
}