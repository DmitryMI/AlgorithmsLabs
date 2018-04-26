#ifndef SEARCH_BISECTION_H
#define SEARCH_BISECTION_H

#include <cmath>

template <typename UnaryFunction>
double SearchBisectionGamma(UnaryFunction function, double precision) {
    double x1 = 0;
    double x2 = 10;

    while (function(x2) < 0)
        x2 *= 1.5;

    double middle = (x2 - x1) / 2;
    double for_function = function(x1);

    do {
        double middle_function = function(middle);

        if (for_function * middle_function < 0)
            x2 = middle;
        else {
            x1 = middle;
            for_function = middle_function;
        }
        middle = x1 + (x2 - x1) / 2;
    } while (std::abs((x2 - x1) / middle) > precision);

    return middle;
}

#endif // SEARCH_BISECTION_H
