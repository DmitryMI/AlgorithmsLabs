#pragma once

#define TOLERANCE 0.001f

class Spline
{
private:
	int point_amount;       // Количество точек
	double *pnt_x, *pnt_y;  // Таблица исходных точек
	double *a, *b, *c, *d;  // Коэффициенты
	void CalculateСoefficients();    // Функция для вычисления коэффициентов
public:
	Spline(double *x, double *y, int count);
	~Spline();

	double calculate(double x);
};

