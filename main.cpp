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

const int kWordNominativeSingular = 1;
const int kWordGenitiveSingularMin = 2;
const int kWordGenitiveSingularMax = 4;

const int kDecimalBase = 10;
}  // namespace

int main() {
    std::cout << "Welcome to the time interpreter!" << std::endl;
    std::cout << "Enter the time in format \"{hours} {minutes}\". {hours} - number from 0 to 23, {minutes} - number from 0 to 59:\nInput: ";

    int hours = kMinHours;
    int minutes = kMinMinutes;
    std::cin >> hours >> minutes;

    if (minutes < kMinMinutes || minutes > kMaxMinutes) {
        std::cout << "Invalid input: \"minutes\" are out of range." << std::endl;
        return 1;
    } else if (hours < kMinHours || hours > kMaxHours) {
        std::cout << "Invalid input: \"hours\" are out of range." << std::endl;
        return 1;
    }

    if (minutes == kMinMinutes) {
        if (hours == kMinHours) {
            std::cout << "полночь;" << std::endl;
            return 0;
        } else if (hours == kMidDayHour) {
            std::cout << "полдень;" << std::endl;
            return 0;
        }
    }

    int hoursFormated = hours > kMidDayHour ? hours - kMidDayHour : hours;

    std::cout << hoursFormated;

    if (hoursFormated == kWordNominativeSingular) {
        std::cout << " час ";
    } else if (hoursFormated >= kWordGenitiveSingularMin && hoursFormated <= kWordGenitiveSingularMax) {
        std::cout << " часа ";
    } else {
        std::cout << " часов ";
    }

    if (minutes != kMinMinutes) {
        std::cout << minutes;
        if (minutes == kWordNominativeSingular ||
            (minutes % kDecimalBase == kWordNominativeSingular && minutes / kDecimalBase != kWordNominativeSingular)) {
            std::cout << " минута ";
        } else if ((minutes % kDecimalBase >= kWordGenitiveSingularMin && minutes % kDecimalBase <= kWordGenitiveSingularMax) &&
                   minutes / kDecimalBase != kWordNominativeSingular) {
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

    std::cout << ";" << std::endl;

    return 0;
}
