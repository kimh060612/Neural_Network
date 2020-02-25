#include "Tensor.h"

Tensor::Tensor()
{
}

Tensor::Tensor(int H, int W, int D)
{
	this->Is3D = true;
	this->Height = H;
	this->Width = W;
	this->Depth = D;
	this->M = new Matrix[D];
	for (int i = 0; i < D; i++)
	{
		this->M[i] = Matrix(H,W);
	}
}

Tensor::Tensor(int H, int W, int D, int Num)
{
	this->Is3D = false;
	this->Height = H;
	this->Width = W;
	this->Depth = D;
	this->NumSet = Num;
	this->FD = new Matrix*[Num];
	for (int i = 0; i < Num; i++)
	{
		this->FD[i] = new Matrix[this->Depth];
		for (int j = 0; j < this->Depth; j++)
		{
			this->FD[i][j] = Matrix(H, W);
		}
	}
}

Tensor::Tensor(Tensor & T)
{
	if (T.Is3D)
	{
		this->Is3D = true;
		this->Height = T.Height;
		this->Width = T.Width;
		this->Depth = T.Depth;
		this->M = new Matrix[T.Depth];
		for (int i = 0; i < T.Depth; i++)
		{
			this->M[i] = Matrix(T.Height, T.Width);
			for (int j = 0; j < T.Height; j++)
			{
				for (int k = 0; k < T.Width; k++)
				{
					this->M[i](j, k) = T(j, k, i);
				}
			}
		}
	}
	else
	{
		this->Is3D = false;
		this->Height = T.Height;
		this->Width = T.Width;
		this->Depth = T.Depth;
		this->NumSet = T.NumSet;
		this->FD = new Matrix*[T.NumSet];
		for (int i = 0; i < T.NumSet; i++)
		{
			this->FD[i] = new Matrix[T.Depth];
			for (int j = 0; j < T.Depth; j++)
			{
				this->FD[i][j] = T.FD[i][j];
			}
		}
	}
}

Tensor::~Tensor()
{
	if (this->Is3D)delete[] this->M;
	else
	{
		for (int i = 0; i < this->NumSet; i++)
		{
			delete[] this->FD[i];
		}
		delete[] this->FD;
	}
}

Tensor & Tensor::operator=(Tensor & T)
{
	if (this == &T)
	{
		return *this;
	}

	if (T.Is3D && this->Is3D)
	{
		if (this->Depth != T.Depth) delete[] this->M; 

		this->Height = T.Height;
		this->Width = T.Width;
		this->Depth = T.Depth;
		this->M = new Matrix[T.Depth];
		for (int i = 0; i < T.Depth; i++)
		{
			this->M[i] = T.M[i];
		}
	}
	else if (!T.Is3D && this->Is3D)
	{
		if (this->Depth != T.Depth) delete[] this->M;

		this->Height = T.Height;
		this->Width = T.Width;
		this->Depth = T.Depth;
		this->NumSet = T.NumSet;
		this->FD = new Matrix*[this->NumSet];
		for (int i = 0; i < this->NumSet; i++)
		{
			this->FD[i] = new Matrix[this->Depth];
			for (int j = 0; j < this->Depth; j++)
			{
				this->FD[i][j] = T.FD[i][j];
			}
		}
	}
	else if (T.Is3D && !this->Is3D)
	{
		for (int i = 0; i < this->NumSet; i++)
		{
			delete[] this->FD[i];
		}
		delete[] this->FD;

		this->Height = T.Height;
		this->Width = T.Width;
		this->Depth = T.Depth;
		this->M = new Matrix[T.Depth];
		for (int i = 0; i < T.Depth; i++)
		{
			this->M[i] = T.M[i];
		}
	}
	else 
	{
		for (int i = 0; i < this->NumSet; i++)
		{
			delete[] this->FD[i];
		}
		delete[] this->FD;

		this->Height = T.Height;
		this->Width = T.Width;
		this->Depth = T.Depth;
		this->NumSet = T.NumSet;
		this->FD = new Matrix*[this->NumSet];
		for (int i = 0; i < this->NumSet; i++)
		{
			this->FD[i] = new Matrix[this->Depth];
			for (int j = 0; j < this->Depth; j++)
			{
				this->FD[i][j] = T.FD[i][j];
			}
		}
	}

	return *this;
}


