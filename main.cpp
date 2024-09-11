#include <iostream>

namespace {
const int kMinHours = 0;
const int kMaxHours = 24;
const int kDaybreakHours = 12;
const int kMinMinutes = 0;
const int kMaxMinutes = 60;

const int kMorningStartHours = 5;
const int kMorningEndHours = 12;
const int kDayStartHours = 12;
const int kDayEndHours = 18;
const int kAfternoonStartHours = 18;
const int kAfternoonEndHours = 23;

const int kDecimalBase = 10;
const int kWordForm1 = 1;
const int kWordForm2 = 2;
const int kWordForm3 = 3;
const int kWordForm4 = 4;
}  // namespace

int main() {
    std::cout << "Welcome to the time interpreter, laba nomer 1!" << std::endl;
    std::cout << "Enter the time: ";

    int hours = kMinHours;
    int minutes = kMinMinutes;
    std::cin >> hours;
    std::cin >> minutes;

    if (hours < kMinHours || hours >= kMaxHours || minutes < kMinMinutes || minutes >= kMaxMinutes) {
        std::cout << "Введены недопустимые данные;" << std::endl;
        return 1;
    }

    if (minutes == kMinMinutes) {
        if (hours == kMinHours) {
            std::cout << "ночь;" << std::endl;
            return 0;
        } else if (hours == kDaybreakHours) {
            std::cout << "полдень;" << std::endl;
            return 0;
        }
    }

    int hoursFormated = hours > kDaybreakHours ? hours - kDaybreakHours : hours;

    std::cout << hoursFormated << " ";

    if (hoursFormated == kWordForm1) {
        std::cout << "час ";
    } else if (hoursFormated == kWordForm2 || hoursFormated == kWordForm3 || hoursFormated == kWordForm4) {
        std::cout << "часа ";
    } else {
        std::cout << "часов ";
    }

    if (minutes != kMaxMinutes) {
        std::cout << minutes << " ";
        if (minutes == kWordForm1 || (minutes % kDecimalBase == kWordForm1 && minutes % kDecimalBase != kWordForm1)) {
            std::cout << "минута ";
        } else if ((minutes % kDecimalBase == kWordForm2 || minutes % kDecimalBase == kWordForm3 || minutes % kDecimalBase == kWordForm4) &&
                   minutes / kDecimalBase != 1) {
            std::cout << "минуты ";
        } else {
            std::cout << "минут ";
        }
    }

    if (hours >= kMorningStartHours && hours < kMorningEndHours) {
        std::cout << "утра";
    } else if (hours >= kDayStartHours && hours < kDayEndHours) {
        std::cout << "дня";
    } else if (hours >= kAfternoonStartHours && hours < kAfternoonEndHours) {
        std::cout << "вечера";
    } else {
        std::cout << "ночи";
    }

    if (minutes == kMinMinutes) {
        std::cout << " ровно";
    }

    std::cout << ";\n";

    return 0;
}
