#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <exception>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>

#include "matrix_components.h"
#include "interpolation.h"
#include "search_bisection.h"
#include "gauss.h"

std::array<std::array<double, 6>, 13> ForMatrix::Q;
std::array<double, 4> ForMatrix::E;
double ForMatrix::relative_precision;
double ForMatrix::gamma_precision;

ForMatrix::~ForMatrix() {
}

ForMatrix::ForMatrix(double for_precision, double for_gamma_precision) {
	relative_precision = for_precision;
	gamma_precision = for_gamma_precision;

	FILE *input_file = fopen("data.txt", "r");

	if (!input_file)
		throw std::exception();

	int error;

	for (size_t i = 0; i < Q.size(); i++) {
        error = fscanf(input_file, "%lf %lf %lf %lf %lf %lf", &Q[i][0], &Q[i][1], &Q[i][2], &Q[i][3], &Q[i][4], &Q[i][5]);
        if (error != 6) { throw std::exception(); }
	}

	for (size_t i = 0; i < E.size(); i++)
		if (fscanf(input_file, "%lf", &E[i]) != 1) { throw std::exception(); }

	fclose(input_file);
}

double ForMatrix::getQ(const double temperature, const int index) {
	int start_index = 0;

	while (Q[start_index][0] < temperature)
		start_index++;

	if (Q[start_index][0] == temperature)
		return Q[start_index][index];

	if (start_index == 0)
		return interpolation(temperature, Q[0][0], Q[1][0], Q[0][index], Q[1][index]);
	else
		return interpolation(temperature, Q[start_index - 1][0], Q[start_index][0], Q[start_index - 1][index], Q[start_index][index]);
}

int ForMatrix::getZ(const int index) {
	return index - 1;
}

double ForMatrix::getE(const int index) {
	return E[index - 1];
}

double ForMatrix::getdE(const double temperature, const double gamma, const int index) {
	double ln = (1 + getZ(index + 1) * getZ(index + 1) * gamma / 2.0) * (1 + gamma / 2.0) / (1 + getZ(index) * getZ(index) * gamma / 2.0);
	return 8.61 * temperature * std::log(ln) * std::pow(10, -5);
}

double ForMatrix::getK(const double temperature, const double gamma, const int index) {
    double exponent = -(getE(index) - getdE(temperature, gamma, index)) * 11603 / temperature;
    return 2 * 2.415 * std::pow(10, -3) * getQ(temperature, index + 1) / getQ(temperature, index) * std::pow(temperature, 3.0 / 2.0) * std::exp(exponent);
}

double ForMatrix::alpha(const double temperature, const double gamma) {
	return 0.285 * std::pow(gamma * temperature, 3) * std::pow(10, -11);
}

double ForMatrix::getGammaAt(const double gamma, const double temperature, const std::array<double, 5>& concentrations) {
	double sum = concentrations[0] / (1 + gamma / 2.0);

    for (size_t i = 2; i < 5; i++) {
		double Zi = getZ(i);
		sum += concentrations[i] * Zi * Zi / (1 + Zi * Zi * gamma / 2.0);
	}

	return gamma * gamma - 5.87 * sum * (std::pow(10, 10)/std::pow(temperature, 3));
}

double ForMatrix::getNextGamma(const double temperature, const std::array<double, 5>& concentrations) {
	auto for_gamma = [&](const double &x) { return getGammaAt(x, temperature, concentrations); };

	return SearchBisectionGamma(for_gamma, gamma_precision);
}

std::array<std::array<double, 6>, 5> ForMatrix::getMatrix(double temperature, double pressure, double gamma, const std::array<double,5>& concentrations) {
	std::array<std::array<double, 6>, 5> matrix;
	std::array<double, 5> exponents;
    std::transform(concentrations.cbegin(), concentrations.cend(), exponents.begin(), [](const double& x) { return std::exp(x); } );

	for (int i = 0; i < 3; i++) {
		matrix[i][0] = 1;
		for (int j = 1; j < 5; j++) {
            if (j == i + 1) matrix[i][j] = -1;
            else if (j == i + 2) matrix[i][j] = 1;
			else matrix[i][j] = 0;
		}
        matrix[i][5] = std::log(getK(temperature, gamma, i + 1)) - (concentrations[0] + concentrations[i + 2] - concentrations[i + 1]);
	}

	matrix[3][0] = matrix[4][0] = exponents[0];

	for (int i = 1; i < 5; i++) {
		matrix[3][i] = exponents[i];
		matrix[4][i] = -getZ(i) * exponents[i];
	}

	matrix[3][5] = 7242 * pressure / temperature + alpha(temperature, gamma) - exponents[0];
	matrix[4][5] = -exponents[0];

	for (int i = 1; i < 5; i++) {
        matrix[3][5] -= exponents[i];
		matrix[4][5] += getZ(i) * exponents[i];
	}

	return matrix;
}

std::array<double, 5> ForMatrix::solveSystem(double temperature, double pressure, double gamma, const std::array<double, 5>& concentrations) {
	std::array<std::array<double, 6>, 5> matrix = getMatrix(temperature, pressure, gamma, concentrations);
    std::array<double, 5> result = gauss<5>(matrix);
	//auto result = gauss(matrix);
    std::transform(concentrations.begin(), concentrations.end(), result.begin(), result.begin(), std::plus<double>());

    return result;
}

std::array<double, 5> ForMatrix::getStartingApproximation(const double temperature, const double pressure) {
	std::array<double, 5> approximations;

    approximations[3] = std::exp(-100);
    approximations[4] = std::exp(-100);

	double k = getK(temperature, 0, 1);
	double ne = std::sqrt(k * k * temperature * temperature + 7242 * k * pressure * temperature) / temperature - k;

	approximations[0] = ne;
	approximations[1] = ne * ne / k;
	approximations[2] = ne;

	return approximations;
}

std::array<double, 5> ForMatrix::getNextConcentrations(const double temperature, const double pressure, std::array<double, 5>& approximations) {
    double gamma = 0;
	std::array<double, 5> differences;	// Δv, Δx_i, etc.
    double max_el;

	do {
        std::for_each(approximations.begin(), approximations.end(), [](double& x){ x = std::log(x);});

		std::array<double, 5> new_values = solveSystem(temperature, pressure, gamma, approximations);

		std::for_each(new_values.begin(), new_values.end(), [](double& x){ x = std::exp(x); });

		std::transform(new_values.begin(), new_values.end(), approximations.begin(),
				differences.begin(),
				[](const double& new_values, const double& old_values) {
                    return (new_values - std::exp(old_values)) / std::exp(old_values);
				});

		approximations = new_values;

		gamma = getNextGamma(temperature, approximations);
        auto min_max = std::minmax_element(differences.begin(), differences.end());
        max_el = std::max(std::abs(*min_max.first), *min_max.second);

    } while (max_el > relative_precision);

	return approximations;
}

double ForMatrix::concentration(const double temperature, const double pressure) {
    double current_temperature = 3000;
    std::array<double, 5> concentrations = getStartingApproximation(current_temperature, pressure);

	while (temperature - current_temperature >= 2000) {
        concentrations = getNextConcentrations(current_temperature, pressure, concentrations);
		current_temperature += 2000;
	}

    concentrations = getNextConcentrations(temperature, pressure, concentrations);

	std::for_each(concentrations.begin(), concentrations.end(), [](double& x){ x *= std::pow(10, 18); });
    return std::accumulate(concentrations.begin()+1, concentrations.end(), 0.0);
}
