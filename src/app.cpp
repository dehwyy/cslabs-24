#include "app.h"
#include <iostream>
#include "collections/matrix.h"
#include "mprinter.h"

namespace app {

void Run() {
    auto matrix = matrix::NewMatrix(3, 3);
    auto b = matrix::NewMatrix(3, 1);

    matrix::FillMatrix(b, [](int, int) { return 2.; });

    // 5x + 3y + z = 2
    // 2x - y + 4z = 2
    // 3x + 4y + 9z = 2
    double values[3][3] = {
        {5., 3.,  1.},
        {2., -1., 4.},
        {3., 4.,  9.}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix.data[i][j] = values[i][j];
        }
    }

    std::cout << "Исходная матрица:" << std::endl;
    mprinter::PrintMatrix(matrix.data, matrix.rows, matrix.cols, 5);
    std::cout << std::endl;

    auto rev_matrix = matrix::GaussJordan(matrix);
    std::cout << "Обратная матрица:" << std::endl;
    mprinter::PrintMatrix(rev_matrix.data, rev_matrix.rows, rev_matrix.cols, 5);
    std::cout << std::endl;

    auto x_matrix = matrix::Multiply(rev_matrix, b);
    std::cout << "Произведение обратной матрицы на свободные члены:" << std::endl;
    mprinter::PrintMatrix(x_matrix.data, x_matrix.rows, x_matrix.cols, 5);

    std::cout << "Произведение матрицы на обратную:" << std::endl;
    auto multiplied = matrix::Multiply(matrix, rev_matrix);
    mprinter::PrintMatrix(multiplied.data, multiplied.rows, multiplied.cols, 12);
    std::cout << std::endl;

    matrix::FreeMatrix(matrix);
    matrix::FreeMatrix(rev_matrix);
    matrix::FreeMatrix(multiplied);
}
}  // namespace app
