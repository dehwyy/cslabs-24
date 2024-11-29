#pragma once

namespace app {
enum class Mode {
    Interactive,
    Demonstration
};

void Run(Mode mode);
}  // namespace app
