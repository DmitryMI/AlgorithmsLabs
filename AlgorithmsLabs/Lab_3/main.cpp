/* Монахов Д.И. ИУ7-44
 * Лабораторная 3. Интерполяция кубическим сплайном
 * 
 * ! Уточнить порядковый номер лаб.р.
*/

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include "Spline.h"
#include <math.h>
#include <iostream>

#define X_INITIAL 0
#define POINT_NUMBER 20
#define POINT_STEP_X 0.25f

double f(double x)
{
	//return sin(x);
	//return 6*sin(x)*log(x+5)/(x+5);
	return x*x*x - 1.5;
	//return cos(x) - x;
}

void GenerateTable(double *x, double *y, double x_init, double x_step, int count)
{
	x[0] = x_init;
	y[0] = f(x_init);
	for (int i = 1; i < count; i++)
	{
		x[i] = x[i - 1] + x_step;
		y[i] = f(x[i]);
	}
}

void PrintTable(double *x, double *y)
{
	printf("====VALUE TABLE====\n");
	for (int i = 0; i < POINT_NUMBER; i++)
	{
		printf("%2.2d: %7.3f   %7.3f\n", i, x[i], y[i]);
	}
	printf("===================\n");
}

int main(void)
{
	double table_x[POINT_NUMBER];
	double table_y[POINT_NUMBER];

	GenerateTable(table_x, table_y, X_INITIAL, POINT_STEP_X, POINT_NUMBER);
	PrintTable(table_x, table_y);

	double x;
	printf("Input X argument: ");
	std::cin >> x;

	if (x > table_x[POINT_NUMBER - 1] || x < table_x[0])
	{		
		printf("Extrapolation is restricted!\n");
		_getch();
		return - 1;
	}

	if (x > table_x[POINT_NUMBER - 2])
	{
		printf("Impossible to build spline basing on this point!\n");
		_getch();
		return -1;
	}

	Spline spline = Spline(table_x, table_y, POINT_NUMBER);

	double y = spline.calculate(x);
	printf("Result: %3.3f\n", y);
	printf("Actual result: %3.3f\n", f(x));

	_getch();
	return 0;
}
