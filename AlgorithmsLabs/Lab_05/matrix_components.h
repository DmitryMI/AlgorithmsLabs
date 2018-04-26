#ifndef MATRIX_COMPONENTS_H
#define MATRIX_COMPONENTS_H

#include <array>

class ForMatrix {
private:
    static double relative_precision;
    static double gamma_precision;

    static double getQ(const double temperature, const int index);
    static int getZ(const int index);
    static double getE(const int index);
    static double getdE(const double temperature, const double gamma, const int index);
    static double getK(const double temperature, const double gamma, const int index);
    static double alpha(const double gamma, const double temperature);
    static double getGammaAt(const double temperature, const double gamma, const std::array<double, 5>& concentrations);
    static double getNextGamma(const double temperature, const std::array<double, 5>& concentrations);

    static std::array<std::array<double, 6>, 5> getMatrix(double temperature, double pressure, double gamma, const std::array<double, 5>& concentrations);
    static std::array<double, 5> solveSystem(double temperature, double pressure, double gamma, const std::array<double, 5>& concentrations);
    static std::array<double, 5> getStartingApproximation(const double temperature, const double pressure);
    static std::array<double, 5> getNextConcentrations(const double temperature, const double pressure, std::array<double, 5> &approximations);
public:
    static std::array<std::array<double, 6>, 13> Q;
    static std::array<double, 4> E;

    ForMatrix(double for_precision, double for_gamma_precision);
    ~ForMatrix();
    static double concentration(const double temperature, const double pressure);
};

#endif // MATRIX_COMPONENTS_H
