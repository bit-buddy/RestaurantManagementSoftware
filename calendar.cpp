#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Helper function to determine if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to calculate the next day given a date in the format DD.MM.YYYY
void getNextDay(int &day, int &month, int &year) {
    // Days in each month (index 0 is ignored for convenience)
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int maxDays = daysInMonth[month];
    if (month == 2 && isLeapYear(year)) {
        maxDays = 29; // February in a leap year
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
