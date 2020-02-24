#include "Matrix.h"
#include <iostream>

using namespace std;

int main()
{
	Matrix A(3,3);
	A.Identity();
	A.show();
	return 0;
}