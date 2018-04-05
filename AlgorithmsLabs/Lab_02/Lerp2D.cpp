#include <stdlib.h>
#include "Lerp2D.h"
#include "../Lab_01/BinarySearch.h"
#include "../Lab_01/Lerp.h"
#include "../Lab_01/NeutonPolinom.h"

double Lerp2D(Table *table, double x, double y, int nx, int ny)
{
	int size = table->get_size();

	double *x_args = table->get_x_args();
	double *y_args = table->get_y_args();
	double *y_nearest = (double*)malloc(sizeof(double)* (ny + 1));
	double *x_nearest = (double*)malloc(sizeof(double)* (nx + 1));
	double *z_interpol = (double*)malloc(sizeof(double)* (ny + 1));
	double *z_vals = (double*)malloc(sizeof(double)*(nx + 1));

	// Определим ny + 1 ближайших точки для аргумента y
	Result bs_result = binarySearch(size, y_args, y);
	int pos = bs_result.pos;

	int offset_right = -(ny + 1) / 2;
	int offset_left = (ny + 1) / 2;
	if ((ny + 1) % 2 == 1)
		offset_left++;

	if (pos + offset_right < 0)
	{
		pos += -pos - offset_right;
		offset_left += -pos - offset_right;
		offset_right += -pos - offset_right;
	}

	if (pos + offset_left > size - 1)
	{
		offset_right -= pos + offset_left - size;
		offset_left -= pos + offset_left - size;
		pos -= pos + offset_left - size;
	}

	for (int j = 0, i = pos + offset_right; i < pos + offset_left; i++, j++)
	{
		y_nearest[j] = y_args[i];
	}

	// Определим nx + 1 ближайших X
	bs_result = binarySearch(size, x_args, x);
	pos = bs_result.pos;

	offset_right = -(nx + 1) / 2;
	offset_left = (nx + 1) / 2;
	if ((nx + 1) % 2 == 1)
		offset_left++;

	if (pos + offset_right < 0)
	{
		pos += -pos - offset_right;
		offset_left += -pos - offset_right;
		offset_right += -pos - offset_right;
	}

	if (pos + offset_left > size - 1)
	{
		offset_right -= pos + offset_left - size;
		offset_left -= pos + offset_left - size;
		pos -= pos + offset_left - size;
	}

	for (int j = 0, i = pos + offset_right; i < pos + offset_left; i++, j++)
	{
		x_nearest[j] = x_args[i];
	}

	// Для каждого ближайшего Y проинтерполируем Z по ближайшим X
	
	for (int i = 0; i < ny + 1; i++)
	{
		for (int j = 0; j < nx + 1; j++)
		{
			z_vals[j] = table->GetZ(x_nearest[j], y_nearest[i]);
		}
		NeutonPolinom polinom = NeutonPolinom(nx, x_nearest, z_vals);
		z_interpol[i] = polinom.Calculate(x);
	} // Здесь мы получаем массив Z, проинтерполированный по X и
	  // имеющий Y == arg_y

	// Интерполируем по Y
	double result;
	NeutonPolinom polinom = NeutonPolinom(ny, y_nearest, z_interpol);
	result = polinom.Calculate(y);
	free(x_args);
	free(y_args);
	free(x_nearest);
	free(y_nearest);
	free(z_vals);
	free(z_interpol);
	return result;
}
