#ifndef __Tensor_H__
#define __Tensor_H__

#include "Matrix.h"

class Tensor // Tensor Object will deal with 3D& 4D Tensor.
{
private:
	// for 3D Tensor
	Matrix* M;
	// for 4D Tensor.
	Matrix ** FD;
	// Discirminator
	bool Is3D;
public:

	int Height;
	int Width;
	int Depth;
	int NumSet = 0;

	Tensor();
	Tensor(int H, int W, int D);
	Tensor(int H, int W, int D, int Num);
	Tensor(Tensor &T);
	~Tensor();

	inline double operator()(int i, int j, int d) { return this->M[d](i, j); }
	inline double operator()(int i, int j, int d, int index) { return this->FD[index][d](i, j); }

	Tensor &operator=(Tensor &T);

};



#endif // !__Tensor_H__


#pragma once
