#include <iostream>

namespace {
const int kMinHours = 0;
const int kMaxHours = 23;
const int kMinMinutes = 0;
const int kMaxMinutes = 59;
const int kMidDayHour = 12;

const int kMorningStartHour = 5;
const int kDayStartHour = 12;
const int kAfternoonStartHour = 18;
const int kNightStartHour = 23;

const int kHoursNominativeSingular = 1;
const int kHoursGenitivePluralMin = 2;
const int kHoursGenitivePluralMax = 4;

const int kMinutesNominativeSingular = 1;
const int kMinutesGenitivePluralMin = 2;
const int kMinutesGenitivePluralMax = 4;

const int kDecimalBase = 10;
}  // namespace

void PrintUsageGuide() {
    std::cout << std::endl
              << "Использование:" << std::endl
              << "[часы] [минуты],\t"
              << "[часы] - число от 0 до 23, [минуты] - число от 0 до 59" << std::endl
              << std::endl;
}

int main(int, char**) {
    std::cout << "Добро пожаловать в интерпретатор времени" << std::endl;
    PrintUsageGuide();
    std::cout << "Ввод: ";

    int hours = kMinHours;
    int minutes = kMinMinutes;
    std::cin >> hours >> minutes;

    bool invalidInput = false;
    if (minutes < kMinMinutes || minutes > kMaxMinutes) {
        std::cout << "Неправильный ввод: \"минуты\" введены неверно." << std::endl;
        invalidInput = true;
    }
    if (hours < kMinHours || hours > kMaxHours) {
        std::cout << "Неправильный ввод: \"часы\" введены неверно." << std::endl;
        invalidInput = true;
    }

    if (invalidInput) {
        PrintUsageGuide();
        return 1;
    }

    if (minutes == kMinMinutes) {
        if (hours == kMinHours) {
            std::cout << "полночь" << std::endl;
            return 0;
        }

        if (hours == kMidDayHour) {
            std::cout << "полдень" << std::endl;
            return 0;
        }
    }

    int hoursFormated = hours > kMidDayHour ? hours - kMidDayHour : hours;

    std::cout << hoursFormated;

    if (hoursFormated == kHoursNominativeSingular) {
        std::cout << " час ";
    } else if (hoursFormated >= kHoursGenitivePluralMin && hoursFormated <= kHoursGenitivePluralMax) {
        std::cout << " часа ";
    } else {
        std::cout << " часов ";
    }

    if (minutes != kMinMinutes) {
        std::cout << minutes;
        int minutesDecimals = minutes / kDecimalBase;
        int minutesUnits = minutes % kDecimalBase;

        if (minutes == kMinutesNominativeSingular || (minutesUnits == kMinutesNominativeSingular && minutesDecimals != kMinutesNominativeSingular)) {
            std::cout << " минута ";
        } else if ((minutesUnits >= kMinutesGenitivePluralMin && minutesUnits <= kMinutesGenitivePluralMax) &&
                   minutesDecimals != kMinutesNominativeSingular) {
            std::cout << " минуты ";
        } else {
            std::cout << " минут ";
        }
    }

    if (hours >= kMorningStartHour && hours < kDayStartHour) {
        std::cout << "утра";
    } else if (hours >= kDayStartHour && hours < kAfternoonStartHour) {
        std::cout << "дня";
    } else if (hours >= kAfternoonStartHour && hours < kNightStartHour) {
        std::cout << "вечера";
    } else {
        std::cout << "ночи";
    }

    if (minutes == kMinMinutes) {
        std::cout << " ровно";
    }

    std::cout << std::endl;

    return 0;
}
