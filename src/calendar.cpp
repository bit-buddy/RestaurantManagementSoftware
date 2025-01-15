/*
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Konstantin Alyakov
* @idnumber 4MI0600453
* @compiler GCC

* <file with helper functions>
*
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include "../include/calendar.h"

using namespace std;

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void getNextDay(int &day, int &month, int &year)
{
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int maxDays = daysInMonth[month];
    if (month == 2 && isLeapYear(year))
    {
        maxDays = 29;
    }

    day++;
    if (day > maxDays)
    {
        day = 1;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }
}
