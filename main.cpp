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
const int kWordNominativeSingular = 1;
const int kWordNominativePluralMin = 2;
const int kWordNominativePluralMax = 4;
}  // namespace

int main() {
    std::cout << "Welcome to the time interpreter!" << std::endl;
    std::cout << "Enter the time in format \"{hours} {minutes}\". {hours} - number from 0 to 23, {minutes} - number from 0 to 59:\nInput: ";

    int hours = kMinHours;
    int minutes = kMinMinutes;
    std::cin >> hours >> minutes;

    if (minutes < kMinMinutes || minutes >= kMaxMinutes) {
        std::cout << "Введены недопустимые данные;" << std::endl;
        return 1;
    } else if (hours < kMinHours || hours >= kMaxHours) {
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

    if (hoursFormated == kWordNominativeSingular) {
        std::cout << "час ";
    } else if (hoursFormated >= kWordNominativePluralMin && hoursFormated <= kWordNominativePluralMax) {
        std::cout << "часа ";
    } else {
        std::cout << "часов ";
    }

    if (minutes != kMaxMinutes) {
        std::cout << minutes << " ";
        if (minutes == kWordNominativeSingular ||
            (minutes % kDecimalBase == kWordNominativeSingular && minutes % kDecimalBase != kWordNominativeSingular)) {
            std::cout << "минута ";
        } else if ((minutes % kDecimalBase >= kWordNominativePluralMin && minutes % kDecimalBase <= kWordNominativePluralMax) &&
                   minutes / kDecimalBase != kWordNominativeSingular) {
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
