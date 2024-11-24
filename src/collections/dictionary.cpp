#include "dictionary.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

namespace {
int BinaryWordSearch(const dict::Dictionary& dict, char* word, bool search_eng) {
    // Sort words in dictionary.
    auto sorted_words = new dict::DictWord[dict.size];
    for (size_t i = 0; i < dict.size; ++i) {
        sorted_words[i] = dict.words[i];
    }

    std::sort(sorted_words, sorted_words + dict.size, [search_eng](const dict::DictWord& a, const dict::DictWord& b) {
        if (search_eng) {
            return strcmp(a.eng_word, b.eng_word) < 0;
        }

        return strcmp(a.rus_word, b.rus_word) < 0;
    });

    // Binary search.
    size_t left = 0;
    size_t right = dict.size - 1;
    while (left <= right) {
        auto middle = (left + right) / 2;

        if (std::strcmp(sorted_words[middle].eng_word, word) == 0) {
            delete[] sorted_words;
            return middle;
        }

        if (std::strcmp(sorted_words[middle].eng_word, word) > 0) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    delete[] sorted_words;
    return -1;
}
}  // namespace

namespace dict {
Dictionary NewDict() {
    return Dictionary{
        .size = 0,
        .capacity = DEFAULT_DICT_CAPACITY,
        .words = new DictWord[DEFAULT_DICT_CAPACITY],
    };
}

void AddWord(Dictionary& dict, char* eng_word, char* rus_word) {
    auto word = DictWord{.eng_word = eng_word, .rus_word = rus_word};

    // Resize dyn array if needed.
    if (dict.size == dict.capacity) {
        dict.capacity *= GROWTH_FACTOR;

        auto new_words = new DictWord[dict.capacity];
        for (size_t i = 0; i < dict.size; ++i) {
            new_words[i] = dict.words[i];
        }
        delete[] dict.words;

        dict.words = new_words;
    }

    dict.words[dict.size++] = word;
}

size_t RemoveWord(Dictionary& dict, char* eng_word) {
    auto idx = BinaryWordSearch(dict, eng_word, true);

    if (idx == -1) {
        return idx;
    }

    for (size_t i = idx; i < dict.size - 1; ++i) {
        dict.words[i] = dict.words[i + 1];
    }

    --dict.size;

    return idx;
}

char* GetEngWord(const Dictionary& dict, char* rus_word) {
    auto idx = BinaryWordSearch(dict, rus_word, true);

    if (idx == -1) {
        return nullptr;
    }

    return dict.words[idx].eng_word;
}

char* GetRusWord(const Dictionary& dict, char* eng_word) {
    auto idx = BinaryWordSearch(dict, eng_word, false);

    if (idx == -1) {
        return nullptr;
    }

    return dict.words[idx].rus_word;
}

void WriteToFile(const Dictionary& dict, char* filepath) {
    std::ofstream file(filepath);
    for (size_t i = 0; i < dict.size; ++i) {
        file << dict.words[i].eng_word << ": " << dict.words[i].rus_word << std::endl;
    }

    file.close();
}

void PrintDict(const Dictionary& dict) {
    for (size_t i = 0; i < dict.size; ++i) {
        std::cout << dict.words[i].eng_word << ": " << dict.words[i].rus_word << std::endl;
    }
}
}  // namespace dict
