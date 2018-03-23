#pragma once

namespace Lab_03
{
	class Matrix
	{
	private:
		double **data;
		int rows, cols;

		static Matrix* ExcludeRowCol(const Matrix& m, int row, int col);
	public:
		Matrix(int rows, int cols);
		Matrix(int rows, int cols, double filler);
		Matrix(const Matrix& m);
		~Matrix();
		int getCols();
		int getRows();

		void setVal(int i, int j, double val);

		double getVal(int i, int j);

		Matrix *inversed();
		Matrix *transposed();

		static double RecursiveDeterminant(const Matrix& m);

		double Determinant();

		static Matrix *prod(const Matrix& a, const Matrix& b);
		static Matrix *prod(const Matrix& a, double k);

		static Matrix *summ(const Matrix& a, const Matrix& b);


	};
}
