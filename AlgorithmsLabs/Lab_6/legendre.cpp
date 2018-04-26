#include "legendre.h"

void legendre_get_roots(double *x, double *polinomial, double *pol_der, int degree)
{
	// »значальные приближени€ дл€ каждого i-того корн€
	for (int i = 0; i < degree; i++)
	{
		x[i] = cosf(M_PI * (4 * i - 1) / (4 * degree + 2));
	}

	/*for (int i = 0; i < degree; i++)
	{
		double *pol
	}*/
}