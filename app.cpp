#include <iostream>

namespace app {

namespace task {
enum class TaskType : int {
    Iteration = 1,
    Newton = 2,
    HalfDivision = 3
};

enum class TaskCastStatus : int {
    Success = 0,
    IncorrectTask = 1
};

struct TaskCast {
    TaskCastStatus status;
    TaskType task;
};

[[nodiscard]] TaskCast CastFromInt(int task) {
    TaskType taskType = static_cast<TaskType>(task);
    TaskCastStatus status = TaskCastStatus::IncorrectTask;

    switch (taskType) {
        case TaskType::Iteration:
            status = TaskCastStatus::Success;
            break;
        case TaskType::Newton:
            status = TaskCastStatus::Success;
            break;
        case TaskType::HalfDivision:
            status = TaskCastStatus::Success;
            break;
    }

    return TaskCast{.status = status, .task = taskType};
}

void Run(TaskType task) {
    switch (task) {
        case TaskType::Iteration:
          std::cout << "Iteration";
          break;
        case TaskType::Newton:
          std::cout << "Newton";
          break;
        case TaskType::HalfDivision:
          std::cout << "HalfDivision";
          break;
  }

  std::cout << "\n";
}

}  // namespace task

int Start() {
    char input = 'y';

    while (input == 'y') {
        std::cout << "Выберите задание:\n"
                  << "1 - Итерационный метод\n"
                  << "2 - Метод Ньютона\n"
                  << "3 - Метод половинного деления\n"
                  << "Ваш выбор: ";

        task::TaskCast castedTask = task::CastFromInt(0);
        while (castedTask.status == task::TaskCastStatus::IncorrectTask) {
            int task = 0;
            std::cin >> task;
            castedTask = task::CastFromInt(task);
        }

        task::Run(castedTask.task);

        std::cout << "Продолжить выполнение? (y/n): ";
        std::cin >> input;
    }

    std::cout << "До свидания.\n";

    return 0;
}
}  // namespace app
