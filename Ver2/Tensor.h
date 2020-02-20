#include "Matrix.h"

class Tensor : public Matrix
{	
public:

	int Dim;
	int Depth_1;
	int Depth_2 = 0;
	int H, W;
	Matrix Tensor_2D;
	Matrix *Tensor_3D;
	Matrix **Tensor_4D;
	int *size;

	//Tensor size array = [Height, Width, Depth1, number of 3D Tensor]
	// if Tensor Dim==2 -> Matrix
	// if Tensor Dim==3 -> size array num 3
	// if Tensor Dim==4 -> size array num 4

	Tensor();
	Tensor(int W, int H);
	Tensor(int W, int H, int D);
	Tensor(int W, int H, int D1, int D2); // Maybe Input only
	Tensor(const Matrix& M);
	Tensor(const Tensor& T);
	Tensor(int *A);

	inline double& operator()(int y, int x, int d, int num) { return this->Tensor_4D[num][d](y, x); }
	inline double& operator()(int y, int x, int d) { return this->Tensor_3D[d](y, x); }
	inline double& operator()(int y, int x) { return this->Tensor_2D(y, x); }

	Tensor &operator=(const Matrix &op1);
	Tensor &operator=(const Tensor &op1);

	~Tensor();
};

Tensor operator+(Tensor &op1, Tensor &op2);
Tensor operator-(Tensor &op1, Tensor &op2);