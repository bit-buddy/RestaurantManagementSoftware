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

* <file with declarations of the functionalities within the turnover.cpp file>
*
*/

#ifndef TURNOVER_H
#define TURNOVER_H
#include "../include/calendar.h"

void updateTurnover(const char *productName, char op);
void showTurnoverForLastDay();
void addNextDayToTurnoverFile();
void printAllTurnovers();

#endif
