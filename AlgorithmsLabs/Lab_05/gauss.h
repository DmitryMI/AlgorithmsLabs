#ifndef GAUSS_H
#define GAUSS_H

template <long unsigned N>
std::array<double, N> gauss(std::array<std::array<double, N + 1>, N>& matrix) {
    for (size_t i = 0; i < N; i++) {
        double max_element = std::abs(matrix[i][i]);
        size_t max_row = i;
        for (size_t k = i + 1; k < N; k++)
            if (abs(matrix[k][i]) > max_element) {
                max_element = std::abs(matrix[k][i]);
                max_row = k;
            }

        std::swap(matrix[max_row], matrix[i]);

        // Make all rows below this one 0 in current column
        for (size_t k = i + 1; k < N; k++) {
            double current = -matrix[k][i] / matrix[i][i];
            matrix[k][i] = 0;
            for (size_t j = i + 1; j < N + 1; j++)
                matrix[k][j] += current * matrix[i][j];
        }
    }

    // Solve equation Ax=b for an upper triangular matrix A
    std::array<double, N> x;

    for (int i = N - 1; i >= 0; i--) {
        x[i] = matrix[i][N] / matrix[i][i];
        for (int k = static_cast<int>(i) - 1;k >= 0; k--)
            matrix[k][N] -= matrix[k][i] * x[i];
    }

    return x;
}

#endif // GAUSS_H
