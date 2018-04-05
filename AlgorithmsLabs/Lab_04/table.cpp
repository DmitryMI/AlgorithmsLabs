#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include "table.h"
namespace Lab_03
{
	void free_table(Table *t)
	{
		if (t == NULL)
			return;
		delete t->x;
		delete t->y;
		delete t->weight;
		delete t;
	}
}