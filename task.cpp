#include <cmath>
#include <iomanip>
#include <iostream>

#include "task.h"

namespace {
const int kMaxIterations = 1e5;
const double kIterativeX0 = 0.1;

struct EquationParameters {
    double k = 0.;
    double epsilon = 0.;
};

struct Segment {
    double xL = 0.;
    double xR = 0.;
};

[[nodiscard]] bool IsValidSegment(Segment segment) {
    return segment.xL < segment.xR;
}

[[nodiscard]] double f(double x, double k) {
    return k * std::cos(x);
}

[[nodiscard]] double fx(double x, double k) {
    return x - f(x, k);
}

[[nodiscard]] double fpx(double x, double k) {
    return 1 + k * std::sin(x);
}

[[nodiscard]] bool IsValidSegmentSigns(Segment segment, double k) {
    bool isLeftPositive = fx(segment.xL, k) > 0;
    bool isRightPositive = fx(segment.xR, k) > 0;

    return isLeftPositive != isRightPositive;
}

[[nodiscard]] EquationParameters ReadEquationParametersFromStdin() {
    std::cout << "Введите коэффициент при cos(x) (вещественное  число): ";
    double k = 0.;
    std::cin >> k;

    std::cout << "Введите погрешность результата научном виде (например: 1e-6): ";
    double epsilon = 0.;
    std::cin >> epsilon;

    return EquationParameters{k, epsilon};
}

[[nodiscard]] double ReadXInitialValueFromStdin() {
    std::cout << "Введите начальное значение поиска x0 (вещественное число): ";
    double x0 = 0.;
    std::cin >> x0;

    return x0;
}

[[nodiscard]] Segment ReadSegmentFromStdin() {
    std::cout << "Введите левую границу отрезка: ";
    double xL = 0.;
    std::cin >> xL;

    std::cout << "Введите правую границу отрезка: ";
    double xR = 0.;
    std::cin >> xR;

    return Segment{xL, xR};
}

void PrintEquationAnswer(task::EquationResult equationResult, double epsilon) {
    if (!equationResult.solved) {
        std::cout << "Не удалось найти корень уравнения при введённых данных\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(std::log10(1 / epsilon)) << "Найденный корень x = " << equationResult.x
              << ", количество итераций: " << equationResult.iterationCount << "\n";
}

}  // namespace

namespace task {
void Run() {
    std::cout << "Выберите задание:\n"
              << "1 - Итерационный метод\n"
              << "2 - Метод Ньютона\n"
              << "3 - Метод половинного деления\n"
              << "Ваш выбор: ";

    int task = 0;
    std::cin >> task;

    switch (static_cast<Task>(task)) {
        case Task::Iteration:
            ExecuteIterationMethod();
            break;
        case Task::Newton:
            ExecuteNewtonMethod();
            break;
        case Task::HalfDivision:
            ExecuteHalfDivisionMethod();
            break;
        default:
            std::cout << "Введенный номер задачи некорректен. Ввод должен быть целым числом от 1 до 3\n";
            break;
    }
}

void ExecuteIterationMethod() {
    EquationParameters params = ReadEquationParametersFromStdin();
    double x0 = ReadXInitialValueFromStdin();

    EquationResult result = CalculateIterationMethod(params.k, params.epsilon, x0);

    PrintEquationAnswer(result, params.epsilon);
}

void ExecuteNewtonMethod() {
    EquationParameters params = ReadEquationParametersFromStdin();
    double x0 = ReadXInitialValueFromStdin();

    EquationResult result = CalculateNewtonMethod(params.k, params.epsilon, x0);

    PrintEquationAnswer(result, params.epsilon);
}

void ExecuteHalfDivisionMethod() {
    EquationParameters params = ReadEquationParametersFromStdin();
    Segment segment = ReadSegmentFromStdin();

    if (!IsValidSegment(segment)) {
        std::cout << "Введены некорректные значения начального отрезка. Левый конец отрезка должен быть меньше правого\n";
        return;
    } else if (!IsValidSegmentSigns(segment, params.k)) {
        std::cout << "Введены некорректные значения начального отрезка. На концах отрезка функция должна принимать значения противоположных знаков\n";
        return;
    }

    EquationResult result = CalculateHalfDivisionMethod(params.k, params.epsilon, segment.xL, segment.xR);

    PrintEquationAnswer(result, params.epsilon);
}

EquationResult CalculateIterationMethod(double k, double epsilon, double x0) {
    double prevX = x0;
    double x = f(prevX, k);

    int iterationCount = 1;

    while (std::fabs(x - prevX) > epsilon && iterationCount < kMaxIterations) {
        prevX = x;
        x = f(x, k);
        ++iterationCount;
    }

    if (iterationCount == kMaxIterations && fx(x, k) > epsilon) {
        return {.solved = false};
    }

    return EquationResult{x, iterationCount};
}

EquationResult CalculateNewtonMethod(double k, double epsilon, double x0) {
    double prevX = x0;
    double x = prevX - fx(prevX, k) / fpx(prevX, k);

    int iterationCount = 1;

    while (std::fabs(x - prevX) > epsilon && iterationCount < kMaxIterations) {
        prevX = x;
        x -= fx(x, k) / fpx(x, k);
        ++iterationCount;
    }

    if (iterationCount == kMaxIterations && fx(x, k) > epsilon) {
        return {.solved = false};
    }

    return EquationResult{x, iterationCount};
}

EquationResult CalculateHalfDivisionMethod(double k, double epsilon, double xL, double xR) {
    int iterationCount = 0;

    while (xR - xL > epsilon) {
        double xM = (xL + xR) / 2;

        if (IsValidSegmentSigns({xL, xM}, k)) {
            xR = xM;
        } else {
            xL = xM;
        }

        ++iterationCount;
    }

    return EquationResult{.x = (xL + xR) / 2, .iterationCount = iterationCount};
}
}  // namespace task
