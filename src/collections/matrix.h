#pragma once

namespace matrix {

using MatrixFillCallback = double (*)(int, int);

struct Matrix {
    int rows = 0;
    int cols = 0;
    double** data = nullptr;
};

Matrix NewMatrix(int rows, int cols);
void FillMatrix(Matrix&, MatrixFillCallback callback);
void FreeMatrix(Matrix&);
Matrix GaussJordan(const Matrix&);
Matrix Multiply(const Matrix&, const Matrix&);
}  // namespace matrix
