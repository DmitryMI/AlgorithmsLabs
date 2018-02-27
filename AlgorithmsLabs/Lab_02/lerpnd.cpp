#include "Lerpnd.h"
#include "../Lab_01/BinarySearch.h"

double lerp1d(double* x_vals, double* y_vals, double arg, int n)
{
	NeutonPolinom polinom = NeutonPolinom(n, x_vals, y_vals);
	return polinom.Calculate(arg);
}


double lerpnd(matrix_t* values, double* arguments, int* degrees, int curarg)
{
	double *z_vals = (double*)malloc(sizeof(double)* degrees[curarg]);
	double *y_vals = (double*)malloc(sizeof(double)* degrees[curarg]);

	// Отберем N различных точек
	// 1) Найдем приблизительное положение аргумента в своем столбце
	int argPos = 0;
	for (; argPos < values->cols; argPos++)
	{
		if (values->data[curarg][argPos] == arguments[curarg])
			break;
	}

	return lerp1d(y_vals, z_vals, arguments[curarg], degrees[curarg]);
}
