#include "app.h"
#include <iostream>
#include "collections/mdict.h"

namespace {
const size_t WORD_CAPACITY = 100;
const dict::DictWord DEFAULT_WORDS[] = {
    {(char*)"Hello",    (char*)"Privet"    },
    {(char*)"World",    (char*)"Mir"       },
    {(char*)"Bye",      (char*)"Poka"      },
    {(char*)"Keyboard", (char*)"Klaviatura"},
    {(char*)"Mouse",    (char*)"Myshka"    },
    {(char*)"Monitor",  (char*)"Monitor"   },
    {(char*)"CPU",      (char*)"Procesor"  },
    {(char*)"Life",     (char*)"Zhizn"     },
    {(char*)"Death",    (char*)"Smert"     },
    {(char*)"Tree",     (char*)"Derevo"    },
};

void CommandAddWord(dict::Dictionary& dict) {
    char eng_word[WORD_CAPACITY];
    std::cout << "Введите английское слово: ";
    std::cin >> eng_word;

    char rus_word[WORD_CAPACITY];
    std::cout << "Введите русское слово: ";
    std::cin >> rus_word;

    dict::AddWord(dict, eng_word, rus_word);

    std::cout << "\nСлово добавлено." << std::endl;
}

void CommandRemoveWord(dict::Dictionary& dict) {
    char word[WORD_CAPACITY];
    std::cout << "Введите слово для удаления: ";
    std::cin >> word;

    dict::RemoveWord(dict, word);
}

void CommandGetEngWord(dict::Dictionary& dict) {
    char word[WORD_CAPACITY];
    std::cout << "Введите слово для поиска: ";
    std::cin >> word;

    char* eng_word = dict::GetEngWord(dict, word);
    if (eng_word != nullptr) {
        std::cout << "\nАнглийское слово: " << eng_word << std::endl;
    } else {
        std::cout << "\nСлово не найдено" << std::endl;
    }
}

void CommandGetRusWord(dict::Dictionary& dict) {
    std::cout << "Введите слово для поиска: ";
    char word[WORD_CAPACITY];
    std::cin >> word;
    char* rus_word = dict::GetRusWord(dict, word);
    if (rus_word != nullptr) {
        std::cout << "\nРусское слово: " << rus_word << std::endl;
    } else {
        std::cout << "\nСлово не найдено" << std::endl;
    }
}

void CommandWriteToFile(dict::Dictionary& dict) {
    dict::WriteToFile(dict, (char*)"dict.txt");
    std::cout << "\nСловарь сохранен в 'dict.txt'" << std::endl;
}

void InteractiveMode() {
    int input = 0;
    auto dict = dict::NewDict();

    while (input != -1) {
        std::cout << "Выберите команду:" << std::endl;
        std::cout << "1. Добавить слово" << std::endl;
        std::cout << "2. Удалить слово" << std::endl;
        std::cout << "3. Найти русское слово по английскому" << std::endl;
        std::cout << "4. Найти английское слово по русскому" << std::endl;
        std::cout << "5. Вывести словарь" << std::endl;
        std::cout << "6. Сохранить словарь в файл" << std::endl;
        std::cout << "7. Выход из программы" << std::endl;
        std::cout << "Введите номер команды: ";

        std::cin >> input;
        switch (static_cast<app::Command>(input)) {
            case app::Command::AddWord:
                CommandAddWord(dict);
                break;
            case app::Command::RemoveWord:
                CommandRemoveWord(dict);
                break;
            case app::Command::GetEngWord:
                CommandGetEngWord(dict);
                break;
            case app::Command::GetRusWord:
                CommandGetRusWord(dict);
                break;
            case app::Command::PrintDict:
                dict::PrintDict(dict);
                break;
            case app::Command::WriteToFile:
                CommandWriteToFile(dict);
                break;
            case app::Command::Exit:
                std::cout << "До свидания!" << std::endl;
                return;
            default:
                std::cout << "Неверная команда" << std::endl;
                break;
        }

        std::cout << std::endl;
    }
}

void DemonstrationMode() {
    auto dict = dict::NewDict();

    std::cout << "Пустой словарь:" << std::endl;
    dict::PrintDict(dict);

    for (const auto& word : DEFAULT_WORDS) {
        dict::AddWord(dict, word.eng_word, word.rus_word);
    }

    std::cout << "Словарь с добавленными словами:" << std::endl;
    dict::PrintDict(dict);

    char* rus_word = dict::GetEngWord(dict, (char*)"Mir");
    std::cout << "Найденное русское слово по ключю 'Mir': " << rus_word << std::endl;

    char* eng_word = dict::GetRusWord(dict, (char*)"Life");
    std::cout << "Найденное английское слово по ключю 'Life': " << eng_word << std::endl;

    dict::RemoveWord(dict, (char*)"World");
    std::cout << "Словарь после удаления слова 'World': " << std::endl;
    dict::PrintDict(dict);

    dict::WriteToFile(dict, (char*)"dict.txt");
    std::cout << "Словарь сохранен в 'dict.txt'" << std::endl;
}
}  // namespace

namespace app {

void Run(Mode mode) {
    switch (mode) {
        case Mode::Interactive:
            InteractiveMode();
            break;
        case Mode::Demonstration:
            DemonstrationMode();
            break;
    }
}
}  // namespace app
