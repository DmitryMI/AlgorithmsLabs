#include <stdio.h>
#include "BinarySearch.h"

struct Result binarySearch(size_t n, double a[], double x)
{
	/* Номер первого элемента в массиве */
	size_t first = 0;
	/* Номер элемента в массиве, СЛЕДУЮЩЕГО ЗА последним */
	size_t last = n;

	/* Начальная проверка, которую, в принципе, можно опустить — но тогда см. ниже! */
	if (n == 0) {
		/* массив пуст */
		return NOTFOUND(0);
	}
	else if (a[0] > x) {
		/* искомый элемент меньше всех в массиве */
		return NOTFOUND(0);
	}
	else if (a[n - 1] < x) {
		/* искомый элемент больше всех в массиве */
		return NOTFOUND(n);
	}

	/* Если просматриваемый участок непустой, first < last */
	while (first < last) {
		size_t mid = first + (last - first) / 2;

		if (x <= a[mid])
			last = mid;
		else
			first = mid + 1;
	}

	/* Если условный оператор if (n == 0) и т.д. в начале опущен -
	* значит, тут раскомментировать!
	*/
	if (/* last < n && */ a[last] == x) {
		/* Искомый элемент найден. last - искомый индекс */
		return FOUND(last);
	}
	else {
		/* Искомый элемент не найден. Но если вам вдруг надо его
		* вставить со сдвигом, то его место - last.
		*/
		return NOTFOUND(last);
	}
}