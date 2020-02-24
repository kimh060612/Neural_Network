#include "READ_MNIST.h"
#include "NeuralNet.h"

// Train Label : "D:\\MNIST\\train-labels-idx1-ubyte\\train-labels.idx1-ubyte"
// Test Label :  "D:\\MNIST\\t10k-labels-idx1-ubyte\\t10k-labels.idx1-ubyte"

// Train Data : "D:\\MNIST\\train-images-idx3-ubyte\\train-images.idx3-ubyte"
// Test Data : "D:\\MNIST\\t10k-images-idx3-ubyte\\t10k-images.idx3-ubyte"

int main()
{
	vector<unsigned char> Train_Label;
	vector<unsigned char> Test_Label;

	Matrix *TrainDATA;
	TrainDATA = new Matrix[10000];
	for (int i = 0; i < 10000; i++)
	{
		Matrix tmp(784, 1);
		TrainDATA[i] = tmp;
	}
	Matrix *TestDATA;
	TestDATA = new Matrix[1000];
	for (int i = 0; i < 1000; i++)
	{
		Matrix tmp(784, 1);
		TestDATA[i] = tmp;
	}

	Matrix *TrainLabel;
	TrainLabel = new Matrix[10000];
	Matrix *TestLabel;
	TestLabel = new Matrix[1000];

	// ÈÆ·Ãµ¥ÀÌÅÍ¸¦ ºÒ·¯¿È
	ReadMNIST_MAT(10000, TrainDATA, "D:\\MNIST\\train-images-idx3-ubyte\\train-images.idx3-ubyte");
	ReadMNISTLabel(10008, Train_Label, "D:\\MNIST\\train-labels-idx1-ubyte\\train-labels.idx1-ubyte"); // ·¹ÀÌºíÀ» ÀÐ¾î ¿È
	// ÈÆ·Ãµ¥ÀÌÅÍ¸¦ ºÒ·¯¿È
	ReadMNIST_MAT(1000, TestDATA, "D:\\MNIST\\t10k-images-idx3-ubyte\\t10k-images.idx3-ubyte");
	ReadMNISTLabel(1008, Test_Label, "D:\\MNIST\\t10k-labels-idx1-ubyte\\t10k-labels.idx1-ubyte"); // ·¹ÀÌºíÀ» ÀÐ¾î ¿È

	int *target_train = new int[10000];
	int *target_test = new int[1000];

	for (int i = 0; i < Train_Label.size(); i++)
	{
		target_train[i] = (int)Train_Label[i];
	}

	for (int i = 0; i < Test_Label.size(); i++)
	{
		target_test[i] = (int)Test_Label[i];
	}

	One_Hot_Encoding(10000, target_train, 10, TrainLabel);
	One_Hot_Encoding(1000, target_test, 10, TestLabel);

	cout << "Complete." << endl;

	/*
	for (int i = 0; i < 10; i++)
	{
		for (int y = 0; y < 28; y++)
		{
			for (int x = 0; x < 28; x++)
			{
				cout << TrainDATA[i]((y * 28) + x, 0) << "   ";
			}
			cout << endl;
		}
	}
	*/

	int NN[4] = { 28 * 28, 100, 100,10 };
	NeuralNet Net(4, NN, 0.5, "Sigmoid");
	//srand((unsigned int)time(NULL));

	Net.SGD(TrainDATA, TrainLabel, 10000,1000,1000);

	delete[] TrainDATA;
	delete[] TrainLabel;
	delete[] TestDATA;
	delete[] TestLabel;
	delete[] target_test;
	delete[] target_train;

	return 0;
}