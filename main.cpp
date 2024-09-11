#include <iostream>

int main() {
    const int MAX_HOURS = 24;
    const int DAYBREAK_HOURS = 12;
    const int MAX_MINUTES = 60;

    const int MORNING_START_HOURS = 5;
    const int MORNING_END_HOURS = 12;
    const int DAY_START_HOURS = 12;
    const int DAY_END_HOURS = 18;
    const int AFTERNOON_START_HOURS = 18;
    const int AFTERNOON_END_HOURS = 23;

    const int DECIMAL_DIGIT = 10;
    const int DIGIT_2 = 2;
    const int DIGIT_3 = 3;
    const int DIGIT_4 = 4;

    int hours = 0;
    int minutes = 0;
    int hoursFormated = 0;
    std::cin >> hours;
    std::cin >> minutes;

    if (hours < 0 || hours >= MAX_HOURS || minutes < 0 || minutes > MAX_MINUTES) {
        std::cout << "Введены недопустимые данные;" << std::endl;
        return 1;
    }

    if (minutes == 0 && (hours == 0 || hours == DAYBREAK_HOURS)) {
        if (hours == 0) {
            std::cout << "полночь;" << std::endl;
        } else {
            std::cout << "полдень;" << std::endl;
        }
        return 0;
    }

    if (hours > DAYBREAK_HOURS) {
        hoursFormated = hours - DAYBREAK_HOURS;
    } else {
        hoursFormated = hours;
    }

    std::cout << hoursFormated << " ";

    if (hoursFormated == 1) {
        std::cout << "час ";
    } else if (hoursFormated == DIGIT_2 || hoursFormated == DIGIT_3 || hoursFormated == DIGIT_4) {
        std::cout << "часа ";
    } else {
        std::cout << "часов ";
    }

    if (minutes != 0) {
        std::cout << minutes << " ";
        if (minutes == 1 || (minutes % DECIMAL_DIGIT == 1 && minutes % DECIMAL_DIGIT != 1)) {
            std::cout << "минута ";
        } else if ((minutes % DECIMAL_DIGIT == DIGIT_2 || minutes % DECIMAL_DIGIT == DIGIT_3 || minutes % DECIMAL_DIGIT == DIGIT_4) &&
                   minutes / DECIMAL_DIGIT != 1) {
            std::cout << "минуты ";
        } else {
            std::cout << "минут ";
        }
    }

    if (hours >= MORNING_START_HOURS && hours < MORNING_END_HOURS) {
        std::cout << "утра";
    } else if (hours > DAY_START_HOURS && hours < DAY_END_HOURS) {
        std::cout << "дня";
    } else if (hours >= AFTERNOON_START_HOURS && hours < AFTERNOON_END_HOURS) {
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
