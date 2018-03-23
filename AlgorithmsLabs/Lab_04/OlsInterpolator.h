#pragma once

#include "table.h"
#include "Matrix.h"

namespace Lab_03
{
	typedef double(*func)(double, int);

	class OlsInterpolator
	{
	private:
		Table *table;
		Matrix *bettas;
		int degree;
		func fi;

	public:
		OlsInterpolator(Table *table, func fi, int degree);
		~OlsInterpolator();
		double calculate(double x);

	};
}
