#include <iostream>

const int kMaxHours = 24;
const int kDaybreakHours = 12;
const int kMaxMinutes = 60;

const int kMorningStartHours = 5;
const int kMorningEndHours = 12;
const int kDayStartHours = 12;
const int kDayEndHours = 18;
const int kAfternoonStartHours = 18;
const int kAfternoonEndHours = 23;

const int kDecimalBase = 10;
const int kDigit2 = 2;
const int kDigit3 = 3;
const int kDigit4 = 4;

int main() {
    int hours = 0;
    int minutes = 0;
    int hoursFormated = 0;
    std::cin >> hours;
    std::cin >> minutes;

    if (hours < 0 || hours >= kMaxHours || minutes < 0 || minutes > kMaxMinutes) {
        std::cout << "Введены недопустимые данные;" << std::endl;
        return 1;
    }

    if (minutes == 0 && (hours == 0 || hours == kDaybreakHours)) {
        if (hours == 0) {
            std::cout << "полночь;" << std::endl;
        } else {
            std::cout << "полдень;" << std::endl;
        }
        return 0;
    }

    if (hours > kDaybreakHours) {
        hoursFormated = hours - kDaybreakHours;
    } else {
        hoursFormated = hours;
    }

    std::cout << hoursFormated << " ";

    if (hoursFormated == 1) {
        std::cout << "час ";
    } else if (hoursFormated == kDigit2 || hoursFormated == kDigit3 || hoursFormated == kDigit4) {
        std::cout << "часа ";
    } else {
        std::cout << "часов ";
    }

    if (minutes != 0) {
        std::cout << minutes << " ";
        if (minutes == 1 || (minutes % kDecimalBase == 1 && minutes % kDecimalBase != 1)) {
            std::cout << "минута ";
        } else if ((minutes % kDecimalBase == kDigit2 || minutes % kDecimalBase == kDigit3 || minutes % kDecimalBase == kDigit4) &&
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

    if (minutes == 0) {
        std::cout << " ровно";
    }

    std::cout << ";\n";

    return 0;
}
