#pragma once

class NeutonPolinom
{
public:
	NeutonPolinom(int n, double *x_arr, double *y_arr);
	~NeutonPolinom();

	double Calculate(double x);

	double DevidedDifferenceIndexated(int count, int start, int *argsInd);

private:
	int N;
	double *xValues;
	double *yValues;
};

