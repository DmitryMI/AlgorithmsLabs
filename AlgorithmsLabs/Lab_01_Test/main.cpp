#include "../Lab_01/NeutonPolinom.h"

int main(void)
{
	NeutonPolinom n = NeutonPolinom(3, new double[] { 1, 2, 3 }, new double[] { 1, 2, 3 });
	n.DevidedDifferenceIndexated(3, 0, new int[] { 0, 1, 2 });
}