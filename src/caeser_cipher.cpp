#include "caeser_cipher.h"
#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace {

const int kMod = 128;

const int kColWeight = 20;

[[nodiscard]] int GetASCII(char c) {
    return static_cast<int>(c);
}

[[nodiscard]] char GetCharByASCII(int asciiCode) {
    return static_cast<char>(asciiCode);
}

[[nodiscard]] bool IsSymbol(char ch) {
    return !(std::ispunct(ch) || std::isspace(ch));
}

char* ProccessText(const char* text, const vec::VecInt& keys, bool encode) {
    const size_t textLength = std::strlen(text);
    char* result = new char[textLength + 1];

    for (size_t i = 0; i <= textLength; i++) {
        int key = vec::GetElement(keys, i % keys.size);
        int asciiCode = GetASCII(text[i]);

        int asciiValue = 0;
        if (encode) {
            asciiValue = (asciiCode + key) % kMod + 1;
        } else {
            asciiValue = (asciiCode - 1 - key) % kMod;
            if (asciiValue < 0) {
                asciiValue += kMod;
            }
        }

        result[i] = GetCharByASCII(asciiValue);
    }

    result[textLength] = '\0';

    return result;
}

}  // namespace

namespace CaesarCipher {

vec::VecInt CreateNotebookKeys(const char* notebook) {
    vec::VecInt keys = vec::CreateVector();

    vec::VecInt word = vec::CreateVector();
    for (size_t i = 0; i < std::strlen(notebook); i++) {
        if (IsSymbol(notebook[i])) {
            vec::Push(word, GetASCII(notebook[i]));
        } else {
            if (word.size > 0) {
                int sum = 0;
                for (size_t j = 0; j < word.size; j++) {
                    sum += word.vector[j];
                }

                vec::Push(keys, sum % kMod);
                vec::ClearVector(word);
            }
        }
    }

    return keys;
}

char* Encode(const char* text, const vec::VecInt& keys) {
    return ProccessText(text, keys, true);
}

char* Decode(const char* text, const vec::VecInt& keys) {
    return ProccessText(text, keys, false);
}

void GenerateStatistics(const char* originalText, const char* encodedText, const vec::VecInt& keys) {
    int asciiFrequency[kMod] = {};
    vec::VecInt uniqueEncodings[kMod] = {};
    for (size_t i = 0; i < kMod; i++) {
        uniqueEncodings[i] = vec::CreateVector();
    }

    size_t originalTextLength = std::strlen(originalText);
    size_t encodedTextLength = std::strlen(encodedText);

    for (size_t i = 0; i <= originalTextLength; i++) {
        int symbol = GetASCII(originalText[i]) % kMod;
        asciiFrequency[symbol]++;
    }

    for (size_t i = 0; i <= encodedTextLength; i++) {
        int ch = GetASCII(originalText[i]);
        int encodedChar = GetASCII(encodedText[i]);

        bool included = false;
        for (size_t j = 0; j < uniqueEncodings[ch].size; j++) {
            if (uniqueEncodings[ch].vector[j] == encodedChar) {
                included = true;
                break;
            }
        }

        if (!included) {
            vec::Push(uniqueEncodings[ch], encodedChar);
        }
    }

    std::cout << "Origin text length: " << originalTextLength << std::endl;
    std::cout << "Notebook words: " << keys.size << std::endl;

    std::cout << std::setw(kColWeight) << "Symbol " << std::setw(kColWeight) << "ASCII Code " << std::setw(kColWeight) << "Frequency "
              << std::setw(kColWeight) << "Unique Encodings " << std::endl;

    for (int i = 0; i < kMod; i++) {
        if (asciiFrequency[i] > 0 && i >= 32) {
            std::cout << std::setw(kColWeight) << GetCharByASCII(i) << std::setw(kColWeight) << i << std::setw(kColWeight) << asciiFrequency[i]
                      << std::setw(kColWeight) << uniqueEncodings[i].size << std::endl;
        }
    }
}

}  // namespace CaesarCipher
