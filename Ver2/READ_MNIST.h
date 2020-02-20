#ifndef __MNIST_H__

#include <iostream>
#include <vector>
#include <fstream>
#include "Matrix.h"
#include <string>

using namespace std;
int ReverseInt(int i);
void ReadMNIST(int NumberOfImages, int DataOfAnImage, vector<vector<double>> &arr, string Path);
void ReadMNISTLabel(int NumberOfLabels, vector<unsigned char> &arr, string Path);
void ReadMNIST_MAT(int NumberOfImages, Matrix *ARR, string Path);

int ReverseInt(int i)
{
	unsigned char ch1, ch2, ch3, ch4;
	ch1 = i & 255;
	ch2 = (i >> 8) & 255;
	ch3 = (i >> 16) & 255;
	ch4 = (i >> 24) & 255;
	return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void ReadMNIST(int NumberOfImages, int DataOfAnImage, vector<vector<double>> &arr, string Path)
{
	arr.resize(NumberOfImages, vector<double>(DataOfAnImage));
	ifstream file(Path, ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;

		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);

		char inputstring[1000];
		for (int i = 0; i < NumberOfImages; ++i)
		{
			for (int r = 0; r < n_rows; ++r)
			{
				for (int c = 0; c < n_cols; ++c)
				{
					unsigned char temp = 0;
					file.read((char*)&temp, sizeof(temp));
					arr[i][(n_rows*r) + c] = ((double)temp/ 255. - 0.5)*2;
				}
			}
			//cout << i << endl;
		}
	}
}

void ReadMNISTLabel(int NumberOfLabels, vector<unsigned char> &arr, string Path)
{
	ifstream file(Path);
	for (int i = 0; i < NumberOfLabels; ++i)
	{
		unsigned char temp = 0;
		file.read((char*)&temp, sizeof(temp));
		if (i > 7)
		{
			arr.push_back((unsigned char)temp);
			//cout << i << endl;
		}
	}
}

void ReadMNIST_MAT(int NumberOfImages,Matrix *ARR, string Path)
{
	//arr.resize(NumberOfImages, vector<double>(DataOfAnImage));
	ifstream file(Path, ios::binary);
	if (file.is_open())
	{
		int magic_number = 0;
		int number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;

		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = ReverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = ReverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = ReverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = ReverseInt(n_cols);

		char inputstring[1000];
		for (int i = 0; i < NumberOfImages; ++i)
		{
			for (int r = 0; r < n_rows; ++r)
			{
				for (int c = 0; c < n_cols; ++c)
				{
					unsigned char temp = 0;
					file.read((char*)&temp, sizeof(temp));
					ARR[i]((n_rows*r) + c, 0) = ((((double)temp)/ 255.) - 0.5)*2;
				}
			}
			cout << i << endl;
		}
	}
}

#endif // !__MNIST_H__


#pragma once
