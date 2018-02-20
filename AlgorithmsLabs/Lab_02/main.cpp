#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <time.h>
#include <conio.h>

#define POINT_NUMBER 30
#define SECTION_NUMBER 6
#define INIT_X 0
#define INIT_Y 0
#define X_STEP 1
#define Y_STEP 1

#define RAND(min, max) (float)rand() / RAND_MAX * (max - min) + min

double func(double x, double y)
{
	return x*x + y*y;
}

void PrintTable(double *x, double *y, double *z)
{
	printf("======= VALUE TABLE =======\n");
	//printf("x")
	for (int i = 0; i < POINT_NUMBER; i++)
	{
		printf("%7.3f   %7.3f   %7.3f\n", x[i], y[i], z[i]);
	}
	printf("===========================\n");
}

void GenerateTable(double *x, double *y, double *z)
{
	for (int j = 0; j < POINT_NUMBER / SECTION_NUMBER; j++)
	{
		int offset = j * SECTION_NUMBER;

		if (j == 0)
		{
			x[offset] = INIT_X;		
		}
		else
		{
			x[offset] = x[offset - SECTION_NUMBER] + X_STEP;
		}
		y[offset] = INIT_Y;
		z[offset] = func(x[offset], y[offset]);
		for (int i = 1; i < SECTION_NUMBER; i++)
		{			
			int shift = offset + i;
			x[shift] = x[shift - 1];
			y[shift] = y[shift - 1] + Y_STEP;
			z[shift] = func(x[shift], y[shift]);
		}
	}
}

int main(void)
{
	srand(time(NULL));

	double x[POINT_NUMBER];
	double y[POINT_NUMBER];
	double z[POINT_NUMBER];

	GenerateTable(x, y, z);
	PrintTable(x, y, z);



	_getch();
}