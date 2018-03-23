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
		free(t->x);
		free(t->y);
		free(t->weight);
		free(t);
	}
}