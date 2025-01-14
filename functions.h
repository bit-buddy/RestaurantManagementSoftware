#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Constants
const int MAX_LEN = 50;
const int MAX_INGREDIENTS = 10;

// Struct to store ingredient data
struct Ingredient
{
    char name[MAX_LEN];
    int quantity;
};

const int MAX_ORDERS = 100;

struct Order
{
    char productName[MAX_LEN];
    int quantity;
};

// Functions related to storage
bool readStorage(Ingredient storage[], int &storageSize);
void writeStorage(Ingredient storage[], int storageSize);
bool removeIngredientsFromStorage(const char *productName);
void recoverIngredients(const char *productName);
void removeProductFromStorage(const char *productName);
void addProductToStorage(const char *productName, int quantity);
void printStorageWithQuantities();
void updateTurnover(const char *productName, char op);
void showTurnoverForLastDay();
bool isLeapYear(int year);
void getNextDay(int &day, int &month, int &year);
void addNextDayToTurnoverFile();
void printAllTurnovers();

// Functions related to orders
bool isProductInMenu(const char *productName);
void updateOrderFile(const char *productName);
bool removeOrderFromFile(const char *productName);
void placeOrder(const char *productName);
void cancelOrder(const char *productName);
void printOrdersWithoutQuantities();
void sortOrdersAlphabetically(Order orders[], int orderCount);
void printSortedOrdersWithQuantities();

// Functions related to menu
void printMenuItems();
void addProductToMenu(const char *productName, double productPrice);
void removeProductFromMenu(const char *productName);

void waiterMenu();
void managerMenu();

#endif // FUNCTIONS_H
