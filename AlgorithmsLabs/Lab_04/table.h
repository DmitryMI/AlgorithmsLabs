#pragma once
namespace Lab_03
{
	class Table
	{
	public:
		float *x;
		float *y;
		float *weight;
		int size;
	};

	void free_table(Table *t);
}