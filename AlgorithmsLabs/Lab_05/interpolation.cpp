#include "interpolation.h"

// Newton interpolation polynomial:
double interpolation(const double x, const double x0, const double x1, const double y0, const double y1) {
    return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
}
