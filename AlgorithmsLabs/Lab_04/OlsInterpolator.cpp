#include "stdafx.h"
#include "OlsInterpolator.h"
#include "Matrix.h"
#include "table.h"
#include <stdio.h>

namespace Lab_03
{

	OlsInterpolator::~OlsInterpolator()
	{
		delete matrix;
		delete col;
		free_table(table);
		delete A;
	}


	void OlsInterpolator::get_slau_matrix()
	{
		int N = table->size;

		// Empty matrix
		matrix = new Matrix(n + 1, n + 1);

		// Empty column
		col = new Matrix(1, n + 1);

		for (int m = 0; m < n + 1; m++)
		{
			for (int i = 0; i < N; i++)
			{
				double tmp = table->weight[i] * fi(table->x[i], m);
				for (int k = 0; k < n + 1; k++)
				{
					double val = table->weight[i] * fi(table->x[i], k);
					double mval = matrix->getVal(m, k);
					mval += tmp * fi(table->x[i], k);
					matrix->setVal(m, k, mval);
					//matrix->setVal(m, k, matrix->getVal(m, k) + tmp * val);
				}
				double cval = col->getVal(0, m);
				cval += tmp * table->y[i];
				col->setVal(0, m, cval);
				//col->setVal(m, 0, col->getVal(m, 0) + tmp * table->y[i]);
			}
		}
	}

	Matrix* solve(Matrix *mat_a, Matrix *z)
	{
		mat_a->print();
		Matrix *inv = mat_a->inversed();
		//inv->print();
		Matrix *c = Matrix::prod(*z, *inv);
		c->print();
		return c;
	}

	
	OlsInterpolator::OlsInterpolator(Table *table, func fi, int degree)
	{
		this->table = table;
		this->fi = fi;
		this->n = degree;
		
		get_slau_matrix();
		A = solve(matrix, col);	
		A->print();
	}

	double *OlsInterpolator::calculate(double start_x, double end_x, double step)
	{
		double *y = new double[(int)(end_x - start_x) + 1];
		int index = 0;
		for (double i = start_x; i <= end_x; i += step, index++)
		{
			double tmp = 0;
			for (int j = 0; j < n + 1; j++)
				tmp += fi(i, j) * A->getVal(0, j);
			y[index] = tmp;
		}
		return y;
	}
}
