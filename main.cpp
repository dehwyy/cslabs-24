#include "app.h"
#include "task.h"

int main(int, char**) {
    app::Run(task::Run);
    return 0;
}
