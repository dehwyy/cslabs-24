#include "app.cpp"
#include "task.cpp"

int main(int, char**) {
  app::Run(task::Run);
  return 0;
}
