#include <iostream>
#include <fstream>
#include <cstring>
#include "../include/calendar.h"

using namespace std;

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void getNextDay(int &day, int &month, int &year) {
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int maxDays = daysInMonth[month];
    if (month == 2 && isLeapYear(year)) {
        maxDays = 29;
    }

    day++;
    if (day > maxDays) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}
