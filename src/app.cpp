#include "app.h"
#include <iostream>
#include "cmath"
#include "collections/matrix.h"
#include "internal/math.h"
#include "internal/random.h"
#include "mprinter.h"

namespace {

const int kMinMatrixSize = 8;
const int kMaxMatrixSize = 15;
const int kMinPrecision = 3;
const int kMaxPrecision = 8;
const int kDecimalBase = 10;
const int x = 1;

const int kStaticMatrixSize = 10;
const double kStaticMatrixB[kStaticMatrixSize][kStaticMatrixSize] = {
    {0,  1,  2,  3,  4,  5,  6,  7,  8,  9 },
    {10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
    {20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
    {30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
    {40, 41, 42, 43, 44, 45, 46, 47, 48, 49},
    {50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
    {60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
    {70, 71, 72, 73, 74, 75, 76, 77, 78, 79},
    {80, 81, 82, 83, 84, 85, 86, 87, 88, 89},
    {90, 91, 92, 93, 94, 95, 96, 97, 98, 99},
};

void RunDynamicMatrix() {
    int rows = randmodule::FromRange(kMinMatrixSize, kMaxMatrixSize);
    int cols = randmodule::FromRange(kMinMatrixSize, kMaxMatrixSize);

    matrix::Matrix matrixA = matrix::NewMatrix(rows, cols);

    matrix::FillMatrix(matrixA, [](int i, int j) -> double {
        // Above main diagonal
        if (j > i) {
            return std::pow(x, i) / std::pow(math::Factorial(j), i);
        }

        // Below main diagonal
        return std::pow(-x, i) / std::pow(math::Factorial(j), i);
    });

    int precision = randmodule::FromRange(kMinPrecision, kMaxPrecision);

    mprinter::PrintMatrix(matrixA.data, rows, cols, precision);
}

void RunStaticMatrix() {
    int precision = randmodule::FromRange(kMinPrecision, kMaxPrecision);

    double** rows_p = new double*[kStaticMatrixSize];
    for (int i = 0; i < kStaticMatrixSize; i++) {
        rows_p[i] = const_cast<double*>(kStaticMatrixB[i]);
    }

    mprinter::PrintMatrix(rows_p, kStaticMatrixSize, kStaticMatrixSize, precision);
}

}  // namespace

namespace app {

void Run() {
    int task = 0;
    std::cout << "Введите номер задания:\n" << "0 - Динамические матрица А\n" << "1 - Статические матрица В\n";
    std::cin >> task;

    switch (static_cast<Task>(task)) {
        case Task::DynamicMatrix:
            RunDynamicMatrix();
            break;
        case Task::StaticMatrix:
            RunStaticMatrix();
            break;
        default:
            std::cout << "Неверный номер задания!\n";
            break;
    }
}
}  // namespace app
