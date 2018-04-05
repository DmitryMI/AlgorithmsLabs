#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "Lerp2D.h"

#include "Table.h"
#include <iostream>

#define TABLE_SIZE 6
#define INIT_ARG 0
#define ARG_STEP 1

double f(double x, double y)
{
	return x*x + y*y;
}

int main(void)
{
	Table *table = new Table(TABLE_SIZE);
	table->GenerateTable(f, INIT_ARG, INIT_ARG, ARG_STEP);
	table->PrintTable();

	int nX, nY;
	double x, y;
	printf("Input Nx: \n");
	std::cin >> nX;
	if (nX >= TABLE_SIZE)
	{
		printf("Not enough points\n");
		_getch();
		return -1;
	}
	printf("Input Ny: \n");
	std::cin >> nY;
	if (nY >= TABLE_SIZE)
	{
		printf("Not enough points\n");
		_getch();
		return -1;
	}
	printf("Input X argument: \n");
	std::cin >> x;
	printf("Input Y argument: \n");
	std::cin >> y;

	
	double result = Lerp2D(table, x, y, nX, nY);
	double actual = f(x, y);
	
	printf("Result: %3.7f\n", result);
	printf("Actual result: %3.7f\n", actual);

	_getch();
	return 0;
}