#include "matrix.h"
#include <cmath>
#include <iostream>
#include "../mprinter.h"

namespace matrix {

Matrix NewMatrix(int rows, int cols) {
    Matrix matrix = {.rows = rows, .cols = cols, .data = new double*[rows]};

    for (int i = 0; i < rows; i++) {
        matrix.data[i] = new double[cols];
    }

    return matrix;
}

void FillMatrix(Matrix& matrix, MatrixFillCallback callback) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            matrix.data[i][j] = callback(i, j);
        }
    }
}

void FreeMatrix(Matrix& matrix) {
    matrix.cols = 0;
    matrix.rows = 0;

    delete[] matrix.data;
}

Matrix GaussJordan(const Matrix& matrix) {
    int n = matrix.rows;

    // Единичная матрица (искомая обратная матрица)
    Matrix i_matrix = NewMatrix(n, n);
    FillMatrix(i_matrix, [](int i, int j) { return i == j ? 1. : 0.; });

    // Матрица, получаемая скреплением Начальной матрицы и единичной
    Matrix augmentMatrix = NewMatrix(n, 2 * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentMatrix.data[i][j] = matrix.data[i][j];
            augmentMatrix.data[i][j + n] = i_matrix.data[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        if (augmentMatrix.data[i][i] == 0) {
            bool once = false;
            // Перестановка строк
            for (int j = i + 1; j < n; j++) {
                if (augmentMatrix.data[j][i] != 0) {
                    std::swap(augmentMatrix.data[i], augmentMatrix.data[j]);
                    once = true;
                    break;
                }
            }

            if (!once) {
                std::cout << "Обратная матрица не существует" << std::endl;
                FreeMatrix(augmentMatrix);
                FreeMatrix(i_matrix);
                exit(1);
                return {};
            }
        }

        for (int j = 0; j < n; j++) {
            if (i != j) {
                auto ratio = augmentMatrix.data[j][i] / augmentMatrix.data[i][i];
                for (int k = 1; k <= 2 * n; k++) {
                    augmentMatrix.data[j][k] = augmentMatrix.data[j][k] - ratio * augmentMatrix.data[i][k];
                }
            }
        }
    }

    // Деление на диагональные элементы
    for (int i = 0; i < n; i++) {
        for (int j = n; j <= 2 * n; j++) {
            augmentMatrix.data[i][j] = augmentMatrix.data[i][j] / augmentMatrix.data[i][i];
        }
    }

    // Перенос данных в новую матрицу
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            i_matrix.data[i][j] = augmentMatrix.data[i][j + n];
        }
    }

    FreeMatrix(augmentMatrix);
    return i_matrix;
}

Matrix Multiply(const Matrix& a, const Matrix& b) {
    if (a.cols != b.rows) {
        std::cout << "Matrixes can't be multiplied" << std::endl;
        return {};
    }

    Matrix result = NewMatrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            double sum = 0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] * b.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}
}  // namespace matrix
