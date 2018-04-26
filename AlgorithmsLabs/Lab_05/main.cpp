#include <iostream>
#include <conio.h>
#include <cmath>
#include "matrix_components.h"

int main(void)
{
    double initial_pressure = 0.1;
    double initial_temperature = 14000;

	std::cout << "State the pressure: ";
	std::cin >> initial_pressure;

	std::cout << "State the temperature: ";
	std::cin >> initial_temperature;

    static ForMatrix input_precision(1e-5, 1e-5);
    double result = ForMatrix::concentration(initial_temperature, initial_pressure);

    std::cout << "Result: "<< result << "\n";
	
	_getch();
    return 0;
}
