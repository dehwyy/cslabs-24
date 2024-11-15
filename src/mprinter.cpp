#include <cmath>
#include <iomanip>
#include <iostream>

namespace mprinter {
void PrintMatrix(double** matrix, int rows, int cols, int precision) {
    int maxElementLenght = 0;
    int el;
    int el_len;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            el = static_cast<int>(matrix[i][j]);

            el_len = el < matrix[i][j] ? 1 : 0;

            while (el > 10) {
                el %= 10;
                el_len++;
            }

            if (el_len > maxElementLenght) {
                maxElementLenght = el_len;
            }
        }
    };

    std::cout << "maxLen" << maxElementLenght << std::endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::left << std::setw(maxElementLenght + precision + 10) << std::fixed << std::setprecision(precision) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}
}  // namespace mprinter
