#pragma once


struct Result { size_t pos; int isFound; };

inline struct Result makeResult(size_t pos, int isFound)
{
	struct Result r;
	r.pos = pos;
	r.isFound = isFound;
	return r;
}

#define FOUND(i)    makeResult(i, 1)
#define NOTFOUND(i) makeResult(i, 0)

struct Result binarySearch(size_t n, double a[], double x);