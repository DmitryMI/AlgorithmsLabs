#include "stdafx.h"
#include "Matrix.h"
#include <stdio.h>
#include <cmath>
#include <fstream>

using namespace System::Windows::Forms;

namespace Lab_03
{

	Matrix::Matrix(const Matrix& m)
	{
		rows = m.rows;
		cols = m.cols;
		data = new double*[m.rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[m.cols];
		}

		for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.cols; i++)
		{
			data[i][j] = m.data[i][j];
		}		
	}

	Matrix::Matrix(int rows, int cols)
	{
		data = new double*[rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
			for (int j = 0; j < cols; j++)
				data[i][j] = 0;
		}
		this->rows = rows;
		this->cols = cols;
	}
	Matrix::Matrix(int rows, int cols, double filler)
	{
		data = new double*[rows];
		for (int i = 0; i < rows; i++)
		{
			data[i] = new double[cols];
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = filler;
			}
		}
		this->rows = rows;
		this->cols = cols;
	}

	Matrix::~Matrix()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] data[i];
		}
		delete data;
	}

	const Matrix *operator *(const Matrix& left, const Matrix& right)
	{
		return Matrix::prod(left, right);
	}

	const Matrix *operator +(const Matrix& left, const Matrix& right)
	{
		return Matrix::summ(left, right);
	}

	void Matrix::setVal(int i, int j, double val)
	{
		data[i][j] = val;
	}

	double Matrix::getVal(int i, int j)
	{
		return data[i][j];
	}

	Matrix* Matrix::prod(const Matrix& a, const Matrix& b)
	{
		if (a.cols != b.rows)
			throw new std::exception();
		Matrix *m = new Matrix(a.rows, b.cols);
		for (int i = 0; i < m->rows; i++)
		for (int j = 0; j < m->cols; j++)
		{
			double res = 0;
			for (int r = 0; r < a.cols; r++)
				res += a.data[i][r] * b.data[r][j];
			m->setVal(i, j, res);
		}
		return m;
	}

	Matrix *Matrix::prod(const Matrix& a, double k)
	{
		Matrix *m = new Matrix(a.rows, a.cols);
		for (int i = 0; i < m->rows; i++)
		for (int j = 0; j < m->cols; j++)
		{
			m->setVal(i, j, m->data[i][j] * k);
		}
		return m;
	}

	Matrix* Matrix::summ(const Matrix& a, const Matrix& b)
	{
		Matrix *m = new Matrix(a.rows, a.cols);
		for (int i = 0; i < m->rows; i++)
		for (int j = 0; j < m->cols; j++)
		{
			m->data[i][j] = a.data[i][j] + b.data[i][j];
		}
		return m;
	}

	Matrix *Matrix::transposed()
	{
		Matrix *tran = new Matrix(rows, cols);
		for (int i = 0; i < rows; ++i)
		{
			for (int j = i; j < cols; ++j)
			{
				tran->data[i][j] = data[j][i];
				tran->data[j][i] = data[i][j];
			}
		}
		return tran;
	}

	Matrix* Matrix::ExcludeRowCol(const Matrix& m, int row, int col)
	{
		Matrix *result = new Matrix(m.rows - 1, m.cols - 1);
		for (int i = 0, x = 0; i < m.rows; i++, x++)
		{
			if (i == row)
			{
				x--;
				continue;
			}
			for (int j = 0, y = 0; j < m.cols; j++, y++)
			{
				if (j == col)
				{
					y--;
					continue;
				}
				result->data[x][y] = m.data[i][j];
			}
		}
		return result;
	}

	double Matrix::RecursiveDeterminant(const Matrix& m)
	{
		if (m.rows == 1 && m.cols == 1)
			return m.data[0][0];
		double result = 0;
		for (int i = 0; i < m.cols; i++)
		{
			Matrix *exc = ExcludeRowCol(m, 0, i);
			if (i % 2 == 0)
				result += m.data[0][i] * RecursiveDeterminant(*exc);
			else
				result -= m.data[0][i] * RecursiveDeterminant(*exc);
			exc->~Matrix();
		}
		return result;
	}

	double Matrix::Determinant()
	{
		return RecursiveDeterminant(*this);
	}

	Matrix *Matrix::inversed()
	{
		Matrix *inv = new Matrix(cols, rows);
		Matrix *tinv;
		this->print();
		double det = Determinant();
		if (det)
		{
			for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
			{
				int m = rows - 1;
				Matrix *tmp = ExcludeRowCol(*this, i, j);
				inv->data[i][j] = pow(-1.0, i + j + 2) * tmp->Determinant() / det;
				tmp->~Matrix();
			}
			inv->print();
			tinv = inv->transposed();
			tinv->print();
			inv->~Matrix();
			return tinv;
		}
		return nullptr;
	}

	void Matrix::print()
	{
		std::ofstream fout;
		fout.open("log.txt");
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				fout << data[i][j];
				fout << " ";
			}
			fout << std::endl;
		}
		fout.close();
	}
}
