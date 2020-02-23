#include "Matrix.h"

Matrix::Matrix()
{
}

Matrix::Matrix(int R, int C)
{
	this->row = R;
	this->col = C;

	this->MAT = new double*[R];
	for (int i = 0; i < R; i++)
	{
		this->MAT[i] = new double[C]();
	}
}

Matrix::Matrix(double **MAT_)
{
	if (_msize(MAT_) / sizeof(double) == 0)
	{
		this->MAT = MAT_;
	}
	else
	{
		this->row = _msize(MAT_) / sizeof(double*);
		this->col = _msize(MAT_[0]) / sizeof(double);
		this->MAT = new double*[this->row];
		for (int i = 0; i < this->row; i++)
		{
			this->MAT[i] = new double[this->col]();
			for (int j = 0; j < this->col; j++)
			{
				this->MAT[i][j] = MAT_[i][j];
			}
		}
	}

}

Matrix::Matrix(const Matrix & MAT_)
{
	this->row = MAT_.row;
	this->col = MAT_.col;
	this->MAT = new double*[MAT_.row];
	for (int i = 0; i < this->row; i++)
	{
		this->MAT[i] = new double[MAT_.col];
	}

	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			this->MAT[i][j] = MAT_.MAT[i][j];
		}
	}

}

Matrix::~Matrix()
{
	if (this->MAT != NULL)
	{
		for (int i = 0; i < this->row; i++)
		{
			delete[] this->MAT[i];
		}
		delete[] this->MAT;

		this->row = 0;
		this->col = 0;
	}
}

Matrix &Matrix::operator=(double **MAT_)
{
	this->row = _msize(MAT_) / sizeof(double*);
	this->col = _msize(MAT_[0]) / sizeof(double);
	this->MAT = MAT_;
	return *this;
}


Matrix operator->*(const Matrix &op1, const Matrix &op2)
{
	if (op2.row != op1.row || op2.col != op1.col)
	{
		cout << "Error: Shape Fault!" << endl;
	}
	else
	{
		Matrix res(op2.row, op2.col);

		for (int i = 0; i < op1.row; i++)
		{
			for (int j = 0; j < op1.col; j++)
			{
				res.MAT[i][j] = op2.MAT[i][j] * op1.MAT[i][j];
			}
		}
		return res;
	}
}

Matrix Trans(Matrix A)
{
	Matrix res(A.col, A.row);

	for (int i = 0; i < A.col; i++)
	{
		for (int j = 0; j < A.row; j++)
		{
			res.MAT[i][j] = A.MAT[j][i];
		}
	}

	return res;
}

inline double * Matrix::PTR_ROW(int index)
{
	if (index <0 || index > this->row)
	{
		cout << "index is not in the range" << endl;
		return NULL;
	}
	else
	{
		double *A = new double[this->row];
		for (int i = 0; i < this->col; i++)
		{
			A[i] = this->MAT[index][i];
		}
		return A;
	}
}

inline double * Matrix::PTR_COL(int index)
{
	if (index <0 || index > this->col)
	{
		cout << "index is not in the range" << endl;
		return NULL;
	}
	else
	{
		double *A = new double[this->row];
		for (int i = 0; i < this->row; i++)
		{
			A[i] = this->MAT[i][index];
		}
		return A;
	}
}

inline double Matrix::EigenValue()
{
	return 0.0;
}

inline Matrix Matrix::EigenVector()
{
	return Matrix();
}

void Matrix::show()
{
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			cout << this->MAT[i][j] << "  ";
		}
		cout << endl;
	}
}


void Matrix::Identity()
{
	if (this->col != this->row)
	{
		cout << "Cannot make Identity" << endl;
	}
	else
	{
		int n = this->row;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)
				{
					this->MAT[i][j] = 1;
				}
				else
				{
					this->MAT[i][j] = 0;
				}

			}
		}
	}

}

Matrix& Matrix::operator+=(const Matrix& m)
{
	for (int i = 0; i < this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
		{
			this->MAT[i][j] += m.MAT[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
	for (int i = 0; i < this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
		{
			this->MAT[i][j] -= m.MAT[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
	Matrix temp(this->row, m.col);
	for (int i = 0; i < temp.row; ++i)
	{
		for (int j = 0; j < temp.col; ++j)
		{
			for (int k = 0; k < this->col; ++k)
			{
				temp.MAT[i][j] += (this->MAT[i][k] * m.MAT[k][j]);
			}
		}
	}
	return (*this = temp);
}

Matrix& Matrix::operator*=(double num)
{
	for (int i = 0; i < this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
		{
			this->MAT[i][j] *= num;
		}
	}
	return *this;
}


Matrix& Matrix::operator/=(double num)
{
	for (int i = 0; i < this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
		{
			this->MAT[i][j] /= num;
		}
	}
	return *this;
}

Matrix Matrix::operator^(int num)
{
	Matrix temp(*this);
	return expHelper(temp, num);
}

Matrix Matrix::expHelper(const Matrix& m, int num)
{
	if (num == 0)
	{
		Matrix A(m.row, m.row);
		A.Identity();
		return A;
	}
	else if (num == 1)
	{
		return m;
	}
	else if (num % 2 == 0)
	{  // num is even
		return expHelper(m * m, num / 2);
	}
	else
	{                    // num is odd
		return m * expHelper(m * m, (num - 1) / 2);
	}
}

Matrix& Matrix::operator=(const Matrix& m)
{
	if (this == &m)
	{
		return *this;
	}

	if (this->row != m.row || this->col != m.col)
	{
		if (this->row > 0 && this->col > 0)
		{
			for (int i = 0; i < this->row; ++i)
			{
				delete[] this->MAT[i];
			}
			delete[] this->MAT;
		}

		this->row = m.row;
		this->col = m.col;

		this->MAT = new double*[this->row];
		for (int i = 0; i < this->row; i++)
		{
			this->MAT[i] = new double[this->col];
		}
	}

	for (int i = 0; i < this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
		{
			this->MAT[i][j] = m.MAT[i][j];
		}
	}
	return *this;
}

double Determinant(Matrix Target) // Same with Inverse_Matrix.
{
	try
	{
		int n;
		double Det = 0;
		if (Target.row != Target.col) { int e = 1; throw(e); }
		n = Target.col;
		Matrix SUBMAT(n - 1, n - 1);
		if (n == 2) return (Target.MAT[0][0] * Target.MAT[1][1] - Target.MAT[0][1] * Target.MAT[1][0]);
		else
		{
			for (int c = 0; c < n; c++)
			{
				int subi = 0;
				for (int i = 1; i < n; i++)
				{
					int subj = 0;
					for (int j = 0; j < n; j++)
					{
						if (j == c)continue;
						SUBMAT.MAT[subi][subj] = Target.MAT[i][j];
						subj++;
					}
					subi++;
				}
				Det = Det + (pow(-1, c) * Target.MAT[0][c] * Determinant(SUBMAT));
			}
		}
		return Det;
	}
	catch (int e)
	{
		cout << "Cannot get the Determinant. this is not the squre matrix" << endl;
	}
}

double CoFactor(Matrix Target, int p, int q)
{
	try
	{
		int n;
		if (Target.col != Target.row) { int e = 1; throw(e); }
		n = Target.col;
		Matrix SUB(n - 1, n - 1);
		int suba = 0;
		for (int i = 0; i < n; i++)
		{
			if (i == p)continue;
			int subb = 0;
			for (int j = 0; j < n; j++)
			{
				if (j == q)continue;
				else
				{
					SUB.MAT[suba][subb] = Target.MAT[i][j];
					subb++;
				}
			}
			suba++;
		}
		return pow(-1, p + q)*Determinant(SUB);
	}
	catch (int e)
	{
		cout << "Cannot get the cofactor. this is not the squre matrix" << endl;
	}
}

Matrix Inverse(Matrix target)
{
	try
	{
		double DET = Determinant(target);
		if (target.col != target.row || DET == double(0))
		{
			int e = 1;
			throw (e);
		}
		else
		{
			int n = target.col;
			Matrix RES(n, n);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					RES.MAT[j][i] = CoFactor(target, i, j);
				}
			}
			RES /= DET;
			return RES;
		}
	}
	catch (int e)
	{
		cout << "Cannot get the Inverse Matrix." << endl;
	}
}

int argmax_1d(double *A, int s, int e)
{
	int max = -987654321;
	for (int i = s; i < e; i++)
	{
		if (max < A[i])max = i;
	}
	return max;
}

Matrix RotPi(Matrix & M)
{
	Matrix res(M.row, M.col);

	for (int i = 0; i < M.row; i++)
	{
		for (int j = 0; j < M.col; j++)
		{
			res(M.row - 1 - i, M.col - 1 - j) = M(i, j);
		}
	}

	return res;
}

Matrix ZeroPadding(Matrix & M, int padding) // 오늘 내일?
{
	return Matrix();
}

Matrix Correlation(Matrix & op1, Matrix & op2, int stride) // 이미 패딩된 값이 들어온다.
{
	int Out_H, Out_W;
	Out_H = ((op1.row - op2.row) / stride) + 1;
	Out_W = ((op1.col - op2.col) / stride) + 1;

	Matrix res(Out_H, Out_W);

	for (int i = 0; i < Out_H; i++)
	{
		for (int j = 0; j < Out_W; j++)
		{
			double sum = 0.;
			for (int p = 0; p < op2.row; p++)
			{
				for (int q = 0; q < op2.col; q++)
				{
					sum += op1(i + stride * p, j + stride * q) * op2(p, q);
				}
			}
			res(i, j) = sum;
		}
	}

	return res;
}

Matrix Convolution(Matrix & op1, Matrix & op2, int stride)
{
	Matrix tmp = RotPi(op2);
	Matrix res = Correlation(op1, tmp, stride);
	return res;
}

Matrix MaxPooling(Matrix & op1, int stride, int * PoolingSize) // 오늘 내일? 이것도 오늘 내일? 잘 모르겠다 일단 Q-learning을 다 짜고 생각을 하자.
{
	int PoolingH = PoolingSize[0];
	int PoolingW = PoolingSize[1];
	int OutH = ((op1.row - PoolingH) / stride) + 1;
	int OutW = ((op1.col - PoolingW) / stride) + 1;
	Matrix res(OutH, OutW);

	for (int i = 0; i < OutH; i++)
	{
		for (int j = 0; j < OutW; j++)
		{
			double Max = -987654321.;
			for (int p = 0; p < PoolingH; p++)
			{
				for (int q = 0; q < PoolingW; q++)
				{
					Max = max(Max, op1(i + stride * p, j + stride * q));
				}
			}
			res(i, j) = Max;
		}
	}

	return res;
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
	Matrix temp(m1);
	return (temp += m2);
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
	Matrix temp(m1);
	return (temp -= m2);
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	Matrix temp(m1);
	return (temp *= m2);
}

Matrix operator*(const Matrix & op1, int Constant)
{
	Matrix tmp(op1);
	return (tmp *= Constant);
}

Matrix operator*(const Matrix& m, double num)
{
	Matrix temp(m);
	return (temp *= num);
}

Matrix operator*(double Constant, const Matrix& m)
{
	return (m * Constant);
}

Matrix operator/(const Matrix& m, double num)
{
	Matrix temp(m);
	return (temp /= num);
}
