#pragma once
#include "collections/matrix.h"

namespace mprinter {
const int kMaxPrintWidth = 80;

void PrintMatrix(const matrix::Matrix&, double epsilon);
}  // namespace mprinter
