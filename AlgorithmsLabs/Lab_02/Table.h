#pragma once
#include <cstdio>


typedef double(func)(double, double);

class Table
{
private:
	double *x_args, *y_args;
	double **data;
	int size;
	double init_x, init_y, step_arg;
public:

	double *get_x_args();
	double *get_y_args();
	double get_init_x();
	double get_init_y();

	int get_size();

	Table(int size);

	double Get(int i, int j);

	double GetZ(double x, double y);
	~Table();

	void GenerateTable(func f, double init_x, double init_y, double step);

	void PrintTable();
};

