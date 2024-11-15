#include "matrix.h"

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
}  // namespace matrix
