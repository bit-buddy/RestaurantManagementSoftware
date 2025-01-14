#ifndef MENU_H
#define MENU_H
#include "../include/constants.h"

//const int MAX_LEN = 50;

void printMenuItems();
void addProductToMenu(const char *productName, double productPrice);
void removeProductFromMenu(const char *productName);

#endif
