#pragma once
#include <stdlib.h>
#include "../Lab_01/Lerp.h"
#include "../Lab_01/NeutonPolinom.h"

typedef struct Matrix
{
	int rows, cols;
	
	// Lines = Array of arguments
	// Cols = Array of points
	double **data;
}matrix_t;

// Values - table of points for interpolation
// degrees = n1, n2, ... , nk - Degrees for polinom. n1 - degree of 1D interp.
double lerpnd(matrix_t *values, double *arguments, int *degrees, int curarg);