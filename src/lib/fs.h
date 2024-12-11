#pragma once

namespace fs {
void WriteFile(const char* filename, const char* content);
char* ReadFile(const char* filename);
}  // namespace fs
