#pragma once

#include "table.h"
#include "Matrix.h"

namespace Lab_03
{
	typedef double(*func)(double, int);

	class OlsInterpolator
	{
	private:
		Table *table;
		Matrix *matrix;
		Matrix *col;
		int n;
		func fi;
		Matrix *A;

		void get_slau_matrix();
	public:
		OlsInterpolator(Table *table, func fi, int degree);
		double *calculate(double start_x, double end_x, double step);
		~OlsInterpolator();

	};
}
