#include "app.h"
#include <iostream>
#include "collections/matrix.h"
#include "mprinter.h"

namespace app {

void Run() {
    auto matrix = matrix::NewMatrix(3, 3);
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
    mprinter::PrintMatrix(matrix.data, matrix.rows, matrix.cols, 1);
    std::cout << std::endl;

    auto rev_matrix = matrix::GaussJordan(matrix);
    std::cout << "Обратная матрица:" << std::endl;
    mprinter::PrintMatrix(rev_matrix.data, rev_matrix.rows, rev_matrix.cols, 5);
    std::cout << std::endl;

    std::cout << "Произведение матрица на обратную:" << std::endl;
    auto multiplied = matrix::Multiply(matrix, rev_matrix);
    mprinter::PrintMatrix(multiplied.data, multiplied.rows, multiplied.cols, 5);
    std::cout << std::endl;

    matrix::FreeMatrix(matrix);
    matrix::FreeMatrix(rev_matrix);
    matrix::FreeMatrix(multiplied);
}
}  // namespace app
