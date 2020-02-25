#include "NeuralNet.h"


NeuralNet::NeuralNet(int Layer_num, int * Node_num, double Learning_rate, string Act_)
{
	this->Act_name = Act_;
	this->Layer_num = Layer_num;
	this->Learning_rate = Learning_rate;

	// First Layer is Input Layer

	this->Node_num = new int[this->Layer_num];
	for (int i = 0; i < this->Layer_num; i++)
	{
		this->Node_num[i] = Node_num[i];
	}

	this->Weight = new Matrix[this->Layer_num];
	for (int i = 1; i < this->Layer_num; i++)
	{
		this->Weight[i] = Matrix(Node_num[i], Node_num[i - 1]);
	}

	this->Node = new Matrix[this->Layer_num];
	for (int i = 0; i < this->Layer_num; i++)
	{
		this->Node[i] = Matrix(Node_num[i], 1);
	}

	this->Delta = new Matrix[this->Layer_num];
	for (int i = 1; i < this->Layer_num; i++) // Useless in Input Layer
	{
		this->Delta[i] = Matrix(Node_num[i], 1);
	}

	this->Bias = new Matrix[this->Layer_num];
	for (int i = 0; i < this->Layer_num; i++)
	{
		this->Bias[i] = Matrix(Node_num[i], 1);
	}

	this->Initialize_Weight();

}

NeuralNet::~NeuralNet()
{
	delete[] this->Weight;
	delete[] this->Node;
	delete[] this->Delta;
}

void NeuralNet::Initialize_Weight()
{
	srand((unsigned int)time(NULL));
	for (int i = 1; i < this->Layer_num; i++)
	{
		for (int j = 0; j < this->Node_num[i]; j++)
		{
			for (int k = 0; k < this->Node_num[i - 1]; k++)
			{
				this->Weight[i](j, k) = (double)rand() / RAND_MAX - 0.5;
			}
		}
	}
}

int NeuralNet::Feed_forward(Matrix *input)
{
	int Max_output = 0;
	double Max = -987654321;
	Act_Func F(this->Act_name);

	for (int i = 0; i < this->Node_num[0]; i++)
	{
		this->Node[0](i, 0) = (*input)(i, 0);
	}

	/*
	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	for (int y = 0; y < 28; y++)
	{
		for (int x = 0; x < 28; x++)
		{
			cout << this->Node[0]((y * 28) + x, 0) << "   ";
		}
		cout << endl;
	}
	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	*/

	for (int i = 1; i < this->Layer_num; i++)
	{
		this->Node[i] = (this->Weight[i] * this->Node[i - 1]) + this->Bias[i];
		this->Node[i] = Feed_Function(this->Node[i], F);
	}

	for (int i = 0; i < this->Node_num[this->Layer_num - 1]; i++)
	{
		if (Max < this->Node[this->Layer_num - 1](i, 0))
		{
			Max = this->Node[this->Layer_num - 1](i, 0);
			Max_output = i;
		}
	}

	return Max_output;
}

void NeuralNet::Calc_Delta(Matrix *target)
{
	Act_Func B(this->Act_name);

	for (int i = this->Layer_num - 1; i > 0; i--)
	{
		if (i == this->Layer_num - 1) this->Delta[i] = (this->Node[this->Layer_num - 1] - (*target))->*Backward_Function(this->Node[this->Layer_num - 1], B);
		else this->Delta[i] = (Trans(this->Weight[i + 1]) * this->Delta[i + 1])->*Backward_Function(this->Node[i], B);
	}

}

void NeuralNet::Update_Weight()
{
	for (int i = this->Layer_num - 1; i > 0; i--)
	{
		this->Weight[i] -= ((this->Learning_rate) * (this->Delta[i] * Trans(this->Node[i - 1])));
		this->Bias[i] -= (this->Learning_rate)*this->Delta[i];
	}
}

int NeuralNet::Train(Matrix *Input, Matrix *Output)
{
	int Max_index = this->Feed_forward(Input);

	this->Calc_Delta(Output);
	this->Update_Weight();

	return Max_index;
}

void NeuralNet::TestModel(Matrix * TestInput, Matrix * TestOutput)
{
}

void NeuralNet::SGD(Matrix * Input, Matrix * Output, int NumData, int BatchSize, int total_epoch)
{
	// Input: Input Set, Output: Outpupt Set
	srand((unsigned int)time(NULL));
	vector<vector<int>> BatchSet = mini_batch_index_generator(NumData, BatchSize);
	int BatchNum = NumData / BatchSize;
	Matrix *BatchGradientWeight;
	Matrix *BatchGradientBias;
	BatchGradientWeight = new Matrix[BatchSize];
	BatchGradientBias = new Matrix[BatchSize];
	for (int i = 1; i < this->Layer_num; i++)
	{
		BatchGradientWeight[i] = Matrix(Node_num[i], Node_num[i - 1]);
	}
	for (int i = 0; i < this->Layer_num; i++)
	{
		BatchGradientBias[i] = Matrix(Node_num[i], 1);
	}

	for (int epoch = 1; epoch <= total_epoch; epoch++)
	{
		int Train_Error = 0;
		double Train_Error_rate = 0.;
		int Test_Error = 0;
		double Test_Error_rate = 0.;
		int BatchIndex = (rand() % BatchNum);

		// Train SGD
		for (int i = 0; i < BatchSize; i++)
		{
			int index = BatchSet[BatchIndex][i];
			int Max_index = this->Feed_forward(&Input[index]);
			this->Calc_Delta(&Output[index]);
			int argmax_O = argmax_1d(Output[index].PTR_COL(0), 0, Output[index].row);
			// Delta 계산
			// Update 계산
			for (int i = this->Layer_num - 1; i > 0; i--)
			{
				BatchGradientWeight[i] += (this->Delta[i] * Trans(this->Node[i - 1]));
				BatchGradientBias[i] += this->Delta[i];
			}
			if (Max_index != argmax_O)Train_Error++;
		}
		//Weight Update
		for (int i = this->Layer_num - 1; i > 0; i--)
		{
			BatchGradientWeight[i] /= (double)BatchSize;
			BatchGradientBias[i] /= (double)BatchSize;
			//Update
			this->Weight[i] -= (this->Learning_rate) * (BatchGradientWeight[i]);
			this->Bias[i] -= (this->Learning_rate)*(BatchGradientBias[i]);
		}
		Train_Error_rate = ((double)Train_Error / (double)BatchSize)*100;

		cout << "-------------------------------------------------------------------" << endl;
		cout << "Epoch: " << epoch << endl;
		cout << "Train Error Rate: " << Train_Error_rate << endl;
		cout << "-------------------------------------------------------------------" << endl;
	}

	delete[] BatchGradientWeight;
	delete[] BatchGradientBias;

}

void NeuralNet::SGD(Matrix & Gradient, double momentum_rate)
{

}

void NeuralNet::Adagrad(Matrix & Graident, double Delta)
{

}

void NeuralNet::RMSProp(Matrix & Gradient, double Delta, double Decay)
{

}

void NeuralNet::Adam(Matrix & Gradient, double Delta, double Decay_F, double decay_S, int time)
{

}



void One_Hot_Encoding(int Data_Num, int *target, int num_class, Matrix *OneHot)
{
	for (int i = 0; i < Data_Num; i++)
	{
		Matrix Tmp(num_class, 1);
		Tmp(target[i], 0) = 1;
		OneHot[i] = Tmp;
	}
}

vector<vector<int>> mini_batch_index_generator(int num_data, int batch_size)
{
	srand((unsigned int)time(NULL));
	if (num_data % batch_size != 0)
	{
		cout << "Error: Batch Size doesn't fit." << endl;
		return vector<vector<int>>();
	}

	int numBatch = num_data / batch_size;
	vector<vector<int>> BatchSet(numBatch, vector<int>(batch_size, 0));

	for (int i = 0; i < numBatch; i++)
	{
		for (int j = 0; j < batch_size; j++)
		{
			BatchSet[i][j] = (numBatch*i) + j;
		}
	}
	return BatchSet;
}
