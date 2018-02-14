#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lab_01/NeutonPolinom.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab_01_Tests
{		
	TEST_CLASS(Lab_01_TestClass)
	{
	public:
		double f(double x)
		{
			return x * x;
		}
		
		TEST_METHOD(DevidedDifferenceTest)
		{
			NeutonPolinom n = NeutonPolinom(4);
			double args[] = { 1, 2, 3, 4 };
		}

	private:
		

	};
}