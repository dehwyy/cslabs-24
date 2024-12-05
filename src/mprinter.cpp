#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kMaxPrintWidth = 80;
const int kColGap = 4;
const int kDecimalBase = 10;

void PrintTableLine(int w, char fill) {
    std::cout << std::setfill(fill) << std::setw(w) << " " << std::setfill(' ') << std::endl;
}
}  // namespace

namespace mprinter {
void PrintMatrix(double** matrix, int rows, int cols, int precision) {
    std::cout << "N = " << cols << " " << " M = " << rows << std::endl;
    std::cout << "Precision: " << precision << std::endl;

    int max_el_len = 0;
    int el = 0;
    int el_len = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            el = std::abs(static_cast<int>(matrix[i][j]));
            el_len = 1;
            if (matrix[i][j] < 0) {
                ++el_len;
            }

            while (el > kDecimalBase) {
                el %= kDecimalBase;
                el_len++;
            }

            if (el_len > max_el_len) {
                max_el_len = el_len;
            }
        }
    };

    const int column_width = max_el_len + precision + kColGap;
    const int cols_per_time = kMaxPrintWidth / column_width;
    const int tableLineLen = cols_per_time * column_width + kColGap;

    int start_col_idx = 0;

    PrintTableLine(tableLineLen, '-');
    while (start_col_idx < cols) {
        for (int i = 0; i < rows; i++) {
            for (int j = start_col_idx; j < start_col_idx + cols_per_time; j++) {
                if (j >= cols) {
                    break;
                }
                std::cout << std::setw(column_width) << std::fixed << std::setprecision(precision) << matrix[i][j];
            }
            std::cout << std::endl;
        }

        start_col_idx += cols_per_time;
        PrintTableLine(tableLineLen, '-');
    }
}
}  // namespace mprinter
