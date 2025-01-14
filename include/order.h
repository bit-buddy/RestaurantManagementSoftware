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
