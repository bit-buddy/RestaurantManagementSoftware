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

* <file with declarations of the functionalities within the menu.cpp file>
*
*/

#ifndef MENU_H
#define MENU_H
#include "../include/constants.h"

//const int MAX_LEN = 50;

void printMenuItems();
void addProductToMenu(const char *productName, double productPrice);
void removeProductFromMenu(const char *productName);

#endif
