#pragma once
namespace Lab_03
{
	typedef struct Table
	{
		float *x;
		float *y;
		float *weight;
		int size;
	};

	void free_table(Table *t);
}