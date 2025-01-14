#ifndef TURNOVER_H
#define TURNOVER_H
#include "../include/calendar.h"

void updateTurnover(const char *productName, char op);
void showTurnoverForLastDay();
void addNextDayToTurnoverFile();
void printAllTurnovers();

#endif
