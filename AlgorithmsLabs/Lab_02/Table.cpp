#include <stdlib.h>
#include "Table.h"


double* Table::get_x_args()
{
	double *tmp = (double*)malloc(sizeof(double)* size);
	for (int i = 0; i < size; i++)
		tmp[i] = x_args[i];
	return tmp;
}
double* Table::get_y_args()
{
	double *tmp = (double*)malloc(sizeof(double)* size);
	for (int i = 0; i < size; i++)
		tmp[i] = y_args[i];
	return tmp;
}

double Table::get_init_x()
{
	return init_x;
}

double Table::get_init_y()
{
	return init_y;
}

int Table::get_size()
{
	return size;
}

Table::Table(int size)
{
	this->size = size;
	data = (double**)malloc(sizeof(double*) * size);
	for (int i = 0; i < size; i++)
	{
		data[i] = (double*)malloc(sizeof(double) * size);
	}
	x_args = (double*)malloc(sizeof(double) * size);
	y_args = (double*)malloc(sizeof(double) * size);
	init_x = 0;
	init_y = 0;
	step_arg = 0;
}

double Table::GetZ(double x, double y)
{
	int i = (x - init_x) / step_arg;
	int j = (y - init_y) / step_arg;
	return data[i][j];
}

Table::~Table()
{
	/*for (int i = 0; i < size; i++)
	{
		free(data[i]);
	}
	free(data);
	free(x_args);
	free(y_args);*/
}

void Table::GenerateTable(func f, double init_x, double init_y, double step)
{
	this->init_x = init_x;
	this->init_y = init_y;
	this->step_arg = step;
	for (int i = 0; i < size; i++)
	{
		double x = init_x + i * step;
		x_args[i] = x;
		for (int j = 0; j < size; j++)
		{			
			if (i == 0)
			{
				double y = init_y + j * step;
				y_args[j] = y;
			}
			data[i][j] = f(x, y_args[j]);
		}
	}
}

void Table::PrintTable()
{
	printf("y\\x  ");
	for (int i = 0; i < size; i++)
	{
		printf("%5.1d ", i);
	}
	printf("\n");

	for (int i = 0; i < size; i++)
	{
		printf("%4.1d ", i);
		for (int j = 0; j < size; j++)
		{
			printf("%5.2f ", data[i][j]);
		}
		printf("\n");
	}
}