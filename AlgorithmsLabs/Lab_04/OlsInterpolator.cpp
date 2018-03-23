#include "stdafx.h"
#include "OlsInterpolator.h"
#include "Matrix.h"
#include "table.h"

namespace Lab_03
{
	OlsInterpolator::OlsInterpolator(Table *table, func fi, int degree)
	{
		this->fi = fi;
		bettas = new Matrix(degree + 1, 1); // Unknown vector
		int point_amount = table->size;
		Matrix *f_mat = new Matrix(point_amount, degree + 1);

		// Filling matrix of values
		for (int i = 0; i < point_amount; i++)
		for (int j = 0; j < degree + 1; j++)
		{
			double fi_k_x = fi(table->x[i], j);
			f_mat->setVal(i, j, fi_k_x);
		}

		// Filling vector of y values
		Matrix yVec = Matrix(point_amount, 1);
		for (int i = 0; i < point_amount; i++)
			yVec.setVal(i, 0, table->y[i]);

		Matrix *t_fmat = f_mat->transposed();
		Matrix *ftf = Matrix::prod(*t_fmat, *f_mat);
		Matrix *ftf_inv = ftf->inversed();
		Matrix *ftf_inv_ft = Matrix::prod(*ftf_inv, *t_fmat);
		bettas = Matrix::prod(*ftf_inv_ft, yVec);
	}

	double OlsInterpolator::calculate(double x)
	{
		double res = 0;
		for (int i = 0; i < degree; i++)
		{
			res += bettas->getVal(i, 0) * fi(x, i);
		}
		return res;
	}
}
