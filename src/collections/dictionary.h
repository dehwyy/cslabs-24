#pragma once
#include <cstddef>

namespace dict {
const int DEFAULT_DICT_CAPACITY = 10;
const int GROWTH_FACTOR = 2;

struct DictWord {
    char* eng_word = {};
    char* rus_word = {};
};
struct Dictionary {
    size_t size = 0;
    size_t capacity = DEFAULT_DICT_CAPACITY;
    DictWord* words = {};
};

Dictionary NewDict();

void AddWord(Dictionary& dict, char* eng_word, char* rus_word);
size_t RemoveWord(Dictionary& dict, char* eng_word);

char* GetRusWord(const Dictionary& dict, char* eng_word);
char* GetEngWord(const Dictionary& dict, char* rus_word);

void WriteToFile(const Dictionary& dict, char* filepath);
void PrintDict(const Dictionary& dict);

}  // namespace dict
