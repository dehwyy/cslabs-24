#pragma once

namespace app {
enum class Mode {
    Interactive,
    Demonstration
};

enum class Command {
    AddWord = 1,
    RemoveWord = 2,
    GetRusWord = 3,
    GetEngWord = 4,
    PrintDict = 5,
    WriteToFile = 6,
    Exit = 7
};

void Run(Mode mode);
}  // namespace app
