#include <stdlib.h>
#include "Spline.h"
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <stdexcept>

#define h(i) (pnt_x[i] - pnt_x[i - 1])
#define F(i) (3 * ((pnt_y[i] - pnt_y[i - 1]) / h(i) - (pnt_y[i - 1] - pnt_y[i - 2]) / h(i - 1)))
#define D(i) h(i)
#define A(i) h(i-1)
#define B(i) (2 * (h(i-1) + h(i)))


Spline::~Spline()
{
	free(pnt_x);
	free(pnt_y);
}

void print_arr(char *title, double *arr, int len)
{
	printf("%s: ", title);
	for (int i = 0; i < len; i++)
	{
		printf("%3.2f ", arr[i]);
	}
	printf("\n");
}

void Spline::CalculateСoefficients()
{
	int steps = point_amount;
	a = (double*)malloc(sizeof(double)* (steps));
	b = (double*)malloc(sizeof(double)* (steps));
	c = (double*)malloc(sizeof(double)* (steps));
	d = (double*)malloc(sizeof(double)* (steps));

	// Прямой ход. Вычислим прогоночные коэффициенты	
	double *e = (double*)malloc(sizeof(double) * (steps + 1));
	double *n = (double*)malloc(sizeof(double)* (steps + 1));
	e[0] = 0;
	n[0] = 0;
	e[1] = 0;
	n[1] = 0;	
	for (int i = 1; i < steps; i++)
	{
		n[i + 1] = (F(i) + A(i) * n[i]) / (B(i) - A(i) * e[i]);
		e[i + 1] = D(i) / (B(i) - A(i) * e[i]);
	}

	// Обратный ход
	c[steps] = 0;
	for (int i = steps - 1; i >= 0; i--)	
		c[i] = e[i + 1] * c[i + 1] + n[i + 1];
	

	// Вычислим a, b, d по найденным c
	a[0] = 0;
	b[0] = 0;
	for (int i = 0; i < steps; i++)
	{
		if (i != 0)
		{
			a[i] = pnt_y[i - 1];
			b[i] = pnt_y[i] - pnt_y[i - 1] - h(i)*(c[i + 1] + 2 * c[i]) / 3;
		}
		d[i] = (c[i + 1] - c[i]) / 3 / h(i);
	}
	d[steps - 1] = -c[steps - 1] / 3 / h(steps - 1);

	free(e);
	free(n);
}

Spline::Spline(double* x, double* y, int count)
{
	if (count < 3)	
		throw std::invalid_argument("Not enough points to create a spline");
	
	point_amount = count;
	size_t size = count * sizeof(double);
	pnt_x = (double*)malloc(size);
	pnt_y = (double*)malloc(size);
	for (int i = 0; i < count; i++)
	{
		pnt_x[i] = x[i];
		pnt_y[i] = y[i];
	}
	CalculateСoefficients();
}

double Spline::calculate(double x)
{
	// Найдем область (Xi и X(i-1))
	int i = 0;
	for (; i < point_amount; i++)
	{
		if (fabs(x - pnt_x[i]) < TOLERANCE)
			return pnt_y[i];
		if (x < pnt_x[i])
			break;
	}
	double h = (x - pnt_x[i - 1]);
	double tmp = h;
	double res =
		a[i] +
		b[i] * tmp +
		c[i] * (tmp *= h) +
		d[i] * (tmp * h);
	return res;
}
