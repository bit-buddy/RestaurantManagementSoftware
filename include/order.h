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

* <file with declarations of the functionalities within the order.cpp file>
*
*/

#ifndef ORDER_H
#define ORDER_H
#include "../include/constants.h"

struct Order
{
    char productName[MAX_LEN];
    int quantity;
};

bool isProductInMenu(const char *productName);
void updateOrderFile(const char *productName);
bool removeOrderFromFile(const char *productName);
void placeOrder(const char *productName);
void cancelOrder(const char *productName);
void printOrdersWithoutQuantities();
void sortOrdersAlphabetically(Order orders[], int orderCount);
void printSortedOrdersWithQuantities();

#endif
