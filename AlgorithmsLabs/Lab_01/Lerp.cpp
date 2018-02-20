#include <stdlib.h>
#include "Lerp.h"
#include "NeutonPolinom.h"
#include "BinarySearch.h"

double Lerp(int argN, double argX, double *x, double *y, int len, int inverse)
{
	int pos = 0;
	if (inverse == 0)
	{
		Result bs_result = binarySearch(len, x, argX);
		pos = bs_result.pos;

		if (bs_result.isFound)
		{
			return y[bs_result.pos];
		}
	}
	else
	{
		double prev = x[0];
		int ind = 0;
		for (ind = 0; ind < len; ind++)
		{
			if (prev * x[ind] <= 0)
				break;
		}
		pos = ind;
	}
	double *x_pol = (double*)malloc(sizeof(double)* (argN + 1));
	double *y_pol = (double*)malloc(sizeof(double)* (argN + 1));
	int offset_right = -(argN + 1) / 2;
	int offset_left = (argN + 1) / 2;
	if ((argN + 1) % 2 == 1)
		offset_left++;

	if (pos + offset_right < 0)
	{
		pos += -pos - offset_right;
		offset_left += -pos - offset_right;
		offset_right += -pos - offset_right;
	}

	if (pos + offset_left > len - 1)
	{
		offset_right -= pos + offset_left - len;
		offset_left -= pos + offset_left - len;
		pos -= pos + offset_left - len;
	}

	for (int j = 0, i = pos + offset_right; i < pos + offset_left; i++, j++)
	{
		x_pol[j] = x[i];
		y_pol[j] = y[i];
	}
	NeutonPolinom polinom = NeutonPolinom(argN, x_pol, y_pol);
	double result = polinom.Calculate(argX);
	return result;
}
