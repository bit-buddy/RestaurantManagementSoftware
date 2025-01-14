#ifndef STORAGE_H
#define STORAGE_H
#include "../include/constants.h"

struct Ingredient
{
    char name[MAX_LEN];
    int quantity;
};

bool readStorage(Ingredient storage[], int &storageSize);
void writeStorage(Ingredient storage[], int storageSize);
bool removeIngredientsFromStorage(const char *productName);
void recoverIngredients(const char *productName);
void removeProductFromStorage(const char *productName);
void addProductToStorage(const char *productName, int quantity);
void printStorageWithQuantities();

#endif
