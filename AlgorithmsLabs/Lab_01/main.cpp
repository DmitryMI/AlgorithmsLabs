#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "NeutonPolinom.h"
#include <conio.h>
#include <math.h>
#include "BinarySearch.h"
#include "iostream"
#include "Lerp.h"

#define X_INITIAL -5.0f
#define POINT_NUMBER 20
#define POINT_STEP_X 1

double f(double x)
{
	//return sin(M_PI / 6 * x);
	return exp(x) - 1.5;
	//return cos(x) - x;
}

void GenerateTable(double *x, double *y)
{
	x[0] = X_INITIAL;
	y[0] = f(X_INITIAL);
	for (int i = 1; i < POINT_NUMBER; i++)
	{
		x[i] = x[i - 1] + POINT_STEP_X;
		y[i] = f(x[i]);
	}
}

void PrintTable(double *x, double *y)
{
	printf("====VALUE TABLE====\n");
	for (int i = 0; i < POINT_NUMBER; i++)
	{
		printf("%7.3f...%7.3f\n", x[i], y[i]);
	}
	printf("===================\n");
}



int main(void)
{
	double x[POINT_NUMBER];
	double y[POINT_NUMBER];

	GenerateTable(x, y);
	PrintTable(x, y);

	double argX = 0;
	int argN = 1;

	std::cout << "Input polinomial degree: ";
	std::cin >> argN;

	if (argN >= POINT_NUMBER)
	{
		printf("Not enough points in table to proceed.\n");
		_getch();
		return -1;
	}

	std::cout << "Input X argument: ";
	std::cin >> argX;

	printf("\n");	

	double result = Lerp(argN, argX, x, y, POINT_NUMBER, 0);
	printf("Interpolated F(X) = %3.3f\n", result);
	printf("Actual F(X) = %3.3f\n", f(argX));

	double root = Lerp(argN, 0, y, x, POINT_NUMBER, 1);
	printf("\nRoot of F(X) == 0: %3.3f\n", root);
	printf("Actual F(root) = %3.3f\n", f(root));
	

	_getch();
}