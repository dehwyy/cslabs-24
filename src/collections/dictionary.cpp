#include "dictionary.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace {
const int COLUMN_WIDTH = 20;

char* BinaryWordSearch(const dict::Dictionary& dict, char* word) {
    // Sort words in dictionary.
    auto sorted_words = new dict::DictWord[dict.size];
    for (size_t i = 0; i < dict.size; ++i) {
        sorted_words[i] = dict.words[i];
    }

    std::sort(sorted_words, sorted_words + dict.size,
              [](const dict::DictWord& a, const dict::DictWord& b) { return strcmp(a.eng_word, b.eng_word) < 0; });

    // Binary search.
    size_t left = 0;
    size_t right = dict.size - 1;
    while (left <= right) {
        auto middle = (left + right) / 2;

        if (std::strcmp(sorted_words[middle].eng_word, word) == 0) {
            size_t len = std::strlen(sorted_words[middle].rus_word);
            char* word = new char(len + 1);
            std::strncpy(word, sorted_words[middle].rus_word, len + 1);

            delete[] sorted_words;
            return word;
        }

        if (std::strcmp(sorted_words[middle].eng_word, word) > 0) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    delete[] sorted_words;

    return nullptr;
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
    auto word = DictWord{.eng_word = new char[strlen(eng_word) + 1], .rus_word = new char[strlen(rus_word) + 1]};

    std::strncpy(word.eng_word, eng_word, strlen(eng_word) + 1);
    std::strncpy(word.rus_word, rus_word, strlen(rus_word) + 1);

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

void RemoveWord(Dictionary& dict, char* eng_word) {
    int word_idx = -1;
    for (size_t i = 0; i < dict.size; ++i) {
        if (word_idx != -1) {
            dict.words[i] = dict.words[i + 1];
            continue;
        }

        if (std::strcmp(dict.words[i].eng_word, eng_word) == 0) {
            word_idx = i;
            --i;
        }
    }

    if (word_idx != -1) {
        --dict.size;
    }
}

// Linear search
char* GetEngWord(const Dictionary& dict, char* rus_word) {
    int idx = -1;
    for (size_t i = 0; i < dict.size; ++i) {
        if (std::strcmp(dict.words[i].rus_word, rus_word) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        return nullptr;
    }

    return dict.words[idx].eng_word;
}

// Binary search
char* GetRusWord(const Dictionary& dict, char* eng_word) {
    return BinaryWordSearch(dict, eng_word);
}

void WriteToFile(const Dictionary& dict, char* filepath) {
    std::ofstream file(filepath, std::ios::out | std::ios::trunc);
    for (size_t i = 0; i < dict.size; ++i) {
        file << dict.words[i].eng_word << ": " << dict.words[i].rus_word << std::endl;
    }

    file.close();
}

void PrintDict(const Dictionary& dict) {
    if (dict.size == 0) {
        std::cout << "Словарь пуст: {}" << std::endl;
        return;
    }

    std::cout << std::setw(COLUMN_WIDTH * 2) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;

    for (size_t i = 0; i < dict.size; ++i) {
        std::cout << std::setw(std::max(static_cast<int>(strlen(dict.words[i].eng_word)), COLUMN_WIDTH)) << dict.words[i].eng_word << std::setw(2)
                  << ": " << std::setw(std::min(COLUMN_WIDTH, static_cast<int>(strlen(dict.words[i].rus_word)))) << dict.words[i].rus_word
                  << std::endl;
    }

    std::cout << std::setw(COLUMN_WIDTH * 2) << std::setfill('-') << "-" << std::setfill(' ') << std::endl;
}
}  // namespace dict
