#include "Tensor.h"

Tensor::Tensor()
{
}

Tensor::Tensor(int W, int H)
{
	this->H = H; this->W = W;
	this->Dim = 2;
	this->Depth_1 = 1;
	this->size = new int[2];
	this->size[0] = H; this->size[1] = W;
	this->Tensor_2D = Matrix(H, W);
}

Tensor::Tensor(int W, int H, int D)
{
	this->H = H; this->W = W;
	this->Dim = 3;
	this->Depth_1 = D;
	this->size = new int[3];
	this->size[0] = H; this->size[1] = W; this->size[2] = D;
	this->Tensor_3D = new Matrix[D];
	for (int i = 0; i < D; i++)
	{
		this->Tensor_3D[i] = Matrix(H, W);
	}
}

Tensor::Tensor(int W, int H, int D1, int D2)
{
	this->H = H; this->W = W;
	this->Dim = 4;
	this->Depth_1 = D1;
	this->Depth_2 = D2;
	this->size = new int[4];
	this->size[0] = H; this->size[1] = W; this->size[2] = D1; this->size[3] = D2;
	this->Tensor_4D = new Matrix*[D1];
	for (int i = 0; i < D1; i++)
	{
		this->Tensor_4D[i] = new Matrix[D2];
	}
	for (int i = 0; i < D1; i++)
	{
		for (int j = 0; j < D2; j++)
		{
			this->Tensor_4D[i][j] = Matrix(H, W);
		}
	}
}

Tensor::Tensor(const Matrix & M)
{
	this->Dim = 2;
	this->size = new int[2]; this->size[0] = M.row; this->size[1] = M.col;
	this->Tensor_2D = M;
}

Tensor::Tensor(const Tensor & T)
{
	this->Dim = sizeof(T.size)/sizeof(int);
	this->size = new int[this->Dim];
	for (int i = 0; i < this->Dim; i++)
	{
		this->size[i] = T.size[i];
	}
	if (Dim == 2) this->Tensor_2D = Matrix(size[0], size[1]);
	else if (Dim == 3)
	{
		this->Tensor_3D = new Matrix[size[2]];
		for (int i = 0; i < size[2]; i++)
		{
			this->Tensor_3D[i] = Matrix(size[0], size[1]);
		}
	}
	else if (Dim == 4)
	{
		this->Tensor_4D = new Matrix*[size[2]];
		for (int i = 0; i < size[2]; i++)
		{
			this->Tensor_4D[i] = new Matrix[size[3]];
			for (int j = 0; j < size[3]; j++)
			{
				this->Tensor_4D[i][j] = Matrix(size[0], size[1]);
			}
		}
	}
	else
	{
		cout << "Dimension Error!" << endl;
	}
}

Tensor::Tensor(int * A)
{
	int N = _msize(A) / sizeof(int);

	if (N == 2)
	{
		this->H = A[0]; this->W = A[1];
		this->Dim = 2;
		this->Depth_1 = 1;
		size = A;
		this->Tensor_2D = Matrix(A[0], A[1]);
	}
	else if (N == 3)
	{
		this->H = A[0]; this->W = A[1];
		this->Dim = 3;
		this->Depth_1 = 4;
		size = A;
		size[0] = A[0]; size[1] = A[1]; size[2] = A[2];
		this->Tensor_3D = new Matrix[A[2]];
		for (int i = 0; i < A[2]; i++)
		{
			this->Tensor_3D[i] = Matrix(A[0], A[1]);
		}
	}
	else if (N == 4)
	{
		this->H = A[0]; this->W = A[1];
		this->Dim = 4;
		this->Depth_1 = A[2];
		this->Depth_2 = A[3];
		size = A;
		this->Tensor_4D = new Matrix*[A[2]];
		for (int i = 0; i < A[2]; i++)
		{
			this->Tensor_4D[i] = new Matrix[A[3]];
		}
		for (int i = 0; i < A[2]; i++)
		{
			for (int j = 0; j < A[3]; j++)
			{
				this->Tensor_4D[i][j] = Matrix(H, W);
			}
		}
	}
	else cout << "Size Error" << endl;

}

Tensor &Tensor::operator=(const Matrix &op1)
{
	if (this->Dim != 2)
	{
		if (this->Dim == 3) { delete[] this->Tensor_3D; delete[] this->size; }
		if (this->Dim == 4)
		{
			for (int i = 0; i < this->size[2]; i++)delete[] this->Tensor_4D[i];
			delete[] this->Tensor_4D;
			delete[] this->size;
		}
	}
	Tensor tmp(op1);
	this->Dim = 2;
	this->size = new int[2]; this->size[0] = op1.row; this->size[1] = op1.col;
	this->Tensor_2D = tmp;
	return *this;
}

Tensor &Tensor::operator=(const Tensor &op1)
{
	if (this->Dim != op1.Dim)
	{
		if (this->Dim == 3) { delete[] this->Tensor_3D; delete[] this->size; }
		if (this->Dim == 4)
		{
			for (int i = 0; i < this->size[2]; i++)delete[] this->Tensor_4D[i];
			delete[] this->Tensor_4D;
			delete[] this->size;
		}
	}

	if (op1.Dim == 3)
	{
		this->Dim = 3;
		this->Tensor_3D = new Matrix[op1.size[2]];
		this->size = new int[3]; this->size[0] = op1.size[0]; this->size[1] = op1.size[1]; this->size[2] = op1.size[2];

		for (int i = 0; i < op1.size[2]; i++)
		{
			this->Tensor_3D[i] = Matrix(this->size[0], this->size[1]);
			this->Tensor_3D[i] = op1.Tensor_3D[i];
		}
	}

	if (op1.Dim == 4)
	{
		this->Dim = 4;
		this->size = new int[3]; this->size[0] = op1.size[0]; this->size[1] = op1.size[1]; this->size[2] = op1.size[2]; this->size[3] = op1.size[3];
		this->Tensor_4D = new Matrix*[op1.size[3]];
		for (int i = 0; i < op1.size[3]; i++)
		{
			this->Tensor_4D[i] = new Matrix[op1.size[2]];
			for (int j = 0; j < op1.size[2]; j++)
			{
				this->Tensor_4D[i][j] = Matrix(this->size[0], this->size[1]);
				this->Tensor_4D[i][j] = op1.Tensor_4D[i][j];
			}
		}
	}

	return *this;
}

Tensor::~Tensor()
{

	if (this->Dim == 3)delete[] this->Tensor_3D;

	if (this->Dim == 4)
	{
		for (int i = 0; i < this->Depth_1; i++)
		{
			delete[] this->Tensor_4D[i];
		}
		delete[] this->Tensor_4D;
	}

}

Tensor operator+(Tensor & op1, Tensor & op2)
{
	return Tensor();
}

Tensor operator-(Tensor & op1, Tensor & op2)
{
	return Tensor();
}
