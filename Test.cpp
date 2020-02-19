#include "READ_MNIST.h"
#include "NeuralNet.h"

// Train Label : "D:\\MNIST\\train-labels-idx1-ubyte\\train-labels.idx1-ubyte"
// Test Label :  "D:\\MNIST\\t10k-labels-idx1-ubyte\\t10k-labels.idx1-ubyte"

// Train Data : "D:\\MNIST\\train-images-idx3-ubyte\\train-images.idx3-ubyte"
// Test Data : "D:\\MNIST\\t10k-images-idx3-ubyte\\t10k-images.idx3-ubyte"

int main()
{
	vector<vector<double>> Train_data;
	vector<unsigned char> Train_Label;
	vector<vector<double>> Test_data;
	vector<unsigned char> Test_Label;

	Matrix *TrainDATA;
	TrainDATA = new Matrix[10000];
	for (int i = 0; i < 10000; i++)
	{
		Matrix tmp(784, 1);
		TrainDATA[i] = tmp;
	}
	Matrix *TestDATA;
	TestDATA = new Matrix[5000];
	for (int i = 0; i < 5000; i++)
	{
		Matrix tmp(784, 1);
		TestDATA[i] = tmp;
	}

	Matrix *TrainLabel;
	TrainLabel = new Matrix[60002];
	Matrix *TestLabel;
	TestLabel = new Matrix[5002];

	//ReadMNIST(10000, 784, Train_data, "D:\\MNIST\\train-images-idx3-ubyte\\train-images.idx3-ubyte"); // ÈÆ·Ãµ¥ÀÌÅÍ¸¦ ºÒ·¯¿È
	ReadMNIST_MAT(10000, TrainDATA, "D:\\MNIST\\train-images-idx3-ubyte\\train-images.idx3-ubyte");
	ReadMNISTLabel(10008, Train_Label, "D:\\MNIST\\train-labels-idx1-ubyte\\train-labels.idx1-ubyte"); // ·¹ÀÌºíÀ» ÀÐ¾î ¿È
	//ReadMNIST(5000, 784, Test_data, "D:\\MNIST\\t10k-images-idx3-ubyte\\t10k-images.idx3-ubyte"); // ÈÆ·Ãµ¥ÀÌÅÍ¸¦ ºÒ·¯¿È
	ReadMNIST_MAT(5000, TestDATA, "D:\\MNIST\\t10k-images-idx3-ubyte\\t10k-images.idx3-ubyte");
	ReadMNISTLabel(5008, Test_Label, "D:\\MNIST\\t10k-labels-idx1-ubyte\\t10k-labels.idx1-ubyte"); // ·¹ÀÌºíÀ» ÀÐ¾î ¿È

	int *target_train = new int[60003];
	int *target_test = new int[5003];

	for (int i = 0; i < Train_Label.size(); i++)
	{
		target_train[i] = (int)Train_Label[i];
	}

	for (int i = 0; i < Test_Label.size(); i++)
	{
		target_test[i] = (int)Test_Label[i];
	}

	One_Hot_Encoding(10000, target_train, 10, TrainLabel);
	One_Hot_Encoding(5000, target_test, 10, TestLabel);

	int NN[4] = {28 * 28, 100, 100,10};
	NeuralNet(4, NN , 0.05, "ReLU");


	return 0;
}