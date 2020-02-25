#include "ActivationFunction.h"

Matrix Feed_Function(Matrix U, Act_Func F)
{

	Matrix res(U.row, U.col);
	for (int i = 0; i < U.row; i++)
	{
		for (int j = 0; j < U.col; j++)
		{
			res(i, j) = F.Forward_Func(U(i, j));
		}
	}

	return res;
}

Matrix Backward_Function(Matrix U, Act_Func De)
{
	Matrix res(U.row, U.col);
	for (int i = 0; i < U.row; i++)
	{
		for (int j = 0; j < U.col; j++)
		{
			res(i, j) = De.Backward_Func(U(i, j));
		}
	}
	return res;

}