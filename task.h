#pragma once

namespace task {
enum class Task : int {
    Iteration = 1,
    Newton = 2,
    HalfDivision = 3
};
struct EquationResult {
    double x = 0.;
    int iterationCount = 0;
    bool solved = true;
};

void Run();

void ExecuteIterationMethod();
void ExecuteNewtonMethod();
void ExecuteHalfDivisionMethod();

[[nodiscard]] EquationResult CalculateIterationMethod(double k, double epsilon, double x0);
[[nodiscard]] EquationResult CalculateNewtonMethod(double k, double epsilon, double x0);
[[nodiscard]] EquationResult CalculateHalfDivisionMethod(double k, double epsilon, double xL, double xR);
}  // namespace task
