#include "matrix.h"

namespace {}

namespace matrix {

Matrix NewMatrix(int rows, int cols) {
    Matrix matrix;

    matrix.rows = rows;
    matrix.cols = cols;

    matrix.data = new double*[rows];
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
    int n = matrix.rows;  // Размерность начальной матрицы

    Matrix i_matrix = NewMatrix(n, n);  // Единичная матрица (искомая обратная матрица)
    FillMatrix(i_matrix, [](int i, int j) { return i == j ? 1. : 0.; });

    Matrix augmentMatrix = NewMatrix(n, 2 * n);  // Матрица, получаемая скреплением Начальной матрицы и единичной
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmentMatrix.data[i][j] = matrix.data[i][j];
            augmentMatrix.data[i][j + n] = i_matrix.data[i][j];
        }
    }

    // Прямой ход (Зануление нижнего левого угла)
    for (int k = 0; k < n; k++)  // k-номер строки
    {
        for (int i = 0; i < 2 * n; i++) {
            // i-номер столбца
            // Деление k-строки на первый член !=0 для преобразования его в единицу
            augmentMatrix.data[k][i] = augmentMatrix.data[k][i] / augmentMatrix.data[k][k];

            for (int i = k + 1; i < n; i++)  // i-номер следующей строки после k
            {
                double koef = augmentMatrix.data[i][k] / augmentMatrix.data[k][k];  // Коэффициент
                for (int j = 0; j < 2 * n; j++) {
                    // j-номер столбца следующей строки после k
                    // Зануление элементов матрицы ниже первого члена, преобразованного в единицу
                    augmentMatrix.data[i][j] = augmentMatrix.data[i][j] - koef * augmentMatrix.data[k][j];
                }
            }
        }
    }

    // Обратный ход (Зануление верхнего правого угла)
    for (int k = n - 1; k > -1; k--)  // k-номер строки
    {
        for (int i = 2 * n - 1; i > -1; i--) {
            augmentMatrix.data[k][i] = augmentMatrix.data[k][i] / augmentMatrix.data[k][k];
            for (int i = k - 1; i > -1; i--)  // i-номер следующей строки после k
            {
                double koef = augmentMatrix.data[i][k] / augmentMatrix.data[k][k];  // Коэффициент
                for (int j = 2 * n - 1; j > -1; j--) {
                    augmentMatrix.data[i][j] = augmentMatrix.data[i][j] - koef * augmentMatrix.data[k][j];
                }
            }
        }  // i-номер столбца
    }

    // Отделяем от общей матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            i_matrix.data[i][j] = augmentMatrix.data[i][j + n];
        }
    }

    FreeMatrix(augmentMatrix);
    return i_matrix;
}
}  // namespace matrix
