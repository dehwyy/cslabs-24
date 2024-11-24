#include "app.h"
#include "collections/dictionary.h"

namespace app {

void Run() {
    auto dict = dict::NewDict();

    dict::AddWord(dict, (char*)"Hello", (char*)"Privet");
    dict::AddWord(dict, (char*)"World", (char*)"Mir");
    dict::AddWord(dict, (char*)"Bye", (char*)"Poka");

    dict::PrintDict(dict);
}
}  // namespace app
