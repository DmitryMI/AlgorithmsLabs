#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "NeutonPolinom.h"

#define DEVDIFF_RECURSIVELY

NeutonPolinom::NeutonPolinom(int n, double *x_arr, double *y_arr)
{
	N = n;
	xValues = (double*)malloc(sizeof(double)* (n + 1));
	yValues = (double*)malloc(sizeof(double)* (n + 1));
	for (int i = 0; i < n + 1; i++)
	{
		xValues[i] = x_arr[i];
		yValues[i] = y_arr[i];
	}
}


NeutonPolinom::~NeutonPolinom()
{
	free(xValues);
	free(yValues);
}

#ifdef DEVDIFF_RECURSIVELY
double NeutonPolinom::DevidedDifferenceIndexated(int count, int* argsInd)
{
	if (count < 2)
		return yValues[argsInd[0]];

	if (count == 2)
	{
		return (yValues[argsInd[1]] - yValues[argsInd[0]]) / (xValues[argsInd[1]] - xValues[argsInd[0]]);
	}

	int *y1_args = (int*)malloc(sizeof(int)* (count - 1));
	int *y2_args = (int*)malloc(sizeof(int)* (count - 1));
	for (int i = 0; i < count - 1; i++)
	{
		y1_args[i] = argsInd[i + 1];
	}
	for (int i = 0; i < count - 1; i++)
	{
		y2_args[i] = argsInd[i];
	}
	double result = (DevidedDifferenceIndexated(count - 1, y1_args) - DevidedDifferenceIndexated(count - 1, y2_args)) / (xValues[argsInd[count - 1]] - xValues[argsInd[0]]);
	free(y1_args);
	free(y2_args);
	return result;
}
#else

#endif


double NeutonPolinom::Calculate(double x)
{
	double result = 0;
	for (int k = 0; k < N + 1; k++)
	{
		if (k == 0)
		{
			result += yValues[0];
			continue;
		}
		int *x_diff_args = (int*)malloc(sizeof(int)* (k + 1));
		x_diff_args[0] = 0;
		double addendum = 1;
		for (int i = 0; i < k; i++)
		{
			addendum *= x - xValues[i];
			x_diff_args[i + 1] = i + 1;
		}
		double dev_diff = DevidedDifferenceIndexated(k + 1, x_diff_args);
		//printf("dev_diff: %3.4f\n", dev_diff);
		addendum *= dev_diff;
		result += addendum;
		free(x_diff_args);
	}
	return result;
}

