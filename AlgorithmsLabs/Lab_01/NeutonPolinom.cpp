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

void PrintArrays(double *x, double *y, int count)
{
	printf("X: ");
	for (int i = 0; i < count; i++)
	{
		printf("%3.3f ", x[i]);
	}
	printf("\nY: ");
	for (int i = 0; i < count; i++)
	{
		printf("%3.3f ", y[i]);
	}
	printf("\n\n");
}

#ifdef DEVDIFF_RECURSIVELY
double NeutonPolinom::DevidedDifferenceIndexated(int count, int start, int* argsInd)
{
	if (count < 2)
		return yValues[argsInd[start + 0]];

	if (count == 2)	
		return (yValues[argsInd[start + 1]] - yValues[argsInd[start + 0]]) / (xValues[argsInd[start + 1]] - xValues[argsInd[start + 0]]);
	
	return (DevidedDifferenceIndexated(count - 1, start + 1, argsInd) - DevidedDifferenceIndexated(count - 1, start, argsInd)) / (xValues[argsInd[count - 1]] - xValues[argsInd[0]]);
}
#else
double NeutonPolinom::DevidedDifferenceIndexated(int count, int start, int* argsInd)
{
	double *values = (double*)malloc(sizeof(double)* count);
	for (int i = 0; i < count; i++)
	{
		values[i] = yValues[argsInd[i]];
	}
	PrintArrays(xValues, values, count);
	for (int k = 1; k < count + 1; k++)
	{
		for (int i = 0; i < count - k; i++)
		{
			values[i] = (values[i] - values[i + 1]) / (xValues[argsInd[i]] - xValues[argsInd[count - k]]);
		}		
		//PrintArrays(xValues, values, count);
	}
	printf("%3.3f\n", values[0]);
	return values[0];
}
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
		double dev_diff = DevidedDifferenceIndexated(k + 1, 0, x_diff_args);
		//printf("dev_diff: %3.4f\n", dev_diff);
		addendum *= dev_diff;
		result += addendum;
		free(x_diff_args);
	}
	return result;
}

