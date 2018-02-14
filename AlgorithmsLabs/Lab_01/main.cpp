#include "stdio.h"
#include "NeutonPolinom.h"
#include <conio.h>
#define _USE_MATH_DEFINES
#include "math.h"

double f(double x)
{
	return sin(M_PI / 6 * x);
}

int main(void)
{
	double x[] = {0, 1, 2, 3};
	double y[] = {0, 0.5, 0.866, 1 };
	NeutonPolinom polinom = NeutonPolinom(f, 4, x, y);
	double res = polinom.Calculate(1.5);
	printf("Polinom: %3.4f\nActual: %3.4f", res, f(1.5));

	_getch();
}