#pragma once

#include <stdlib.h>

	typedef double (*func_t)(double x);

	class NeutonPolinom
	{
	public:
		NeutonPolinom(func_t func, int n, double *x_arr, double *y_arr);
		~NeutonPolinom();

		double Calculate(double x);

		double DevidedDifference(int count, double *args);

		double DevidedDifferenceIndexated(int count, int *argsInd);

	private:
		int N;
		double *xValues;
		double *yValues;
		func_t function;
	};

