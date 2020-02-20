#include "Optimizer.h"

vector<vector<int>> mini_batch_index_generator(int num_data, int batch_size)
{
	srand((unsigned int)time(NULL));
	if (num_data % batch_size != 0)
	{
		cout << "Error: Batch Size doesn't fit." << endl;
		return vector<vector<int>>();
	}

	int numBatch = num_data / batch_size;
	vector<vector<int>> BatchSet(numBatch, vector<int>(batch_size ,0));

	for (int i = 0; i < numBatch; i++)
	{
		for (int j = 0; j < batch_size; j++)
		{
			BatchSet[i][j] = (numBatch*i) + j;
		}
	}
	return BatchSet;
}

Optimizer::Optimizer(string Name, int NB, int BS)
{
	this->Optimizer_type = Name;
	this->BatchSet = mini_batch_index_generator(NB, BS);
}

Matrix Optimizer::SGD(Matrix & Gradient)
{
	srand((unsigned int)time(NULL));



	return Matrix();
}

Matrix Optimizer::SGD(Matrix & Gradient, double momentum_rate)
{
	return Matrix();
}

Matrix Optimizer::Adagrad(Matrix & Graident, double Delta)
{
	return Matrix();
}

Matrix Optimizer::RMSProp(Matrix & Gradient, double Delta, double Decay)
{
	return Matrix();
}

Matrix Optimizer::Adam(Matrix & Gradient, double Delta, double Decay_F, double decay_S, int time)
{
	return Matrix();
}
