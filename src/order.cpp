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

* <file with definitions of the functionalities within the order.h file>
*
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include "../include/order.h"
#include "../include/storage.h"
#include "../include/turnover.h"

using namespace std;

// Function to check if the product is in the menu
bool isProductInMenu(const char *productName)
{
    ifstream menuFile("../data/menu.txt");
    if (!menuFile)
    {
        cout << "Error opening the menu file!" << endl;
        return false;
    }

    char line[MAX_LEN];
    while (menuFile.getline(line, MAX_LEN))
    {
        char existingProduct[MAX_LEN];
        sscanf(line, "%s", existingProduct);
        if (strcmp(existingProduct, productName) == 0)
        {
            return true;
        }
    }

    return false;
}

void updateOrderFile(const char *productName)
{
    fstream ordersFile("../data/orders.txt", ios::in | ios::out);
    if (!ordersFile)
    {
        cout << "Error opening the orders file!" << endl;
        return;
    }

    char line[MAX_LEN];
    bool productFound = false;
    char content[MAX_LEN * 1000] = "";

    while (ordersFile.getline(line, MAX_LEN))
    {
        char existingProduct[MAX_LEN];
        int count;
        sscanf(line, "%s %d", existingProduct, &count);
        if (strcmp(existingProduct, productName) == 0)
        {
            count++;
            productFound = true;
        }
        char temp[MAX_LEN];
        snprintf(temp, MAX_LEN, "%s %d\n", existingProduct, count);
        strcat(content, temp);
    }

    if (!productFound)
    {
        char temp[MAX_LEN];
        snprintf(temp, MAX_LEN, "%s 1\n", productName);
        strcat(content, temp);
    }
    ordersFile.close();

    ofstream overwriteFile("../data/orders.txt");
    overwriteFile << content;
    overwriteFile.close();

    cout << "Order for " << productName << " was placed successfully" << endl;
}

bool removeOrderFromFile(const char *productName)
{
    fstream ordersFile("../data/orders.txt", ios::in | ios::out);
    if (!ordersFile)
    {
        cout << "Error: Unable to open orders file!" << endl;
    }

    char line[50];
    bool productFound = false;
    int count = 0;
    char updatedOrders[1000] = "";

    while (ordersFile.getline(line, sizeof(line)))
    {
        char existingProduct[50];
        int existingCount;
        sscanf(line, "%s %d", existingProduct, &existingCount);

        if (strcmp(existingProduct, productName) == 0)
        {
            productFound = true;
            count = existingCount;
            existingCount--;
        }

        if (existingCount > 0)
        {
            char temp[50];
            snprintf(temp, sizeof(temp), "%s %d\n", existingProduct, existingCount);
            strcat(updatedOrders, temp);
        }
    }
    ordersFile.close();

    if (!productFound)
    {
        cout << "Error: No order found for " << productName << " to cancel." << endl;
        return false;
    }

    ofstream overwriteOrders("../data/orders.txt");
    overwriteOrders << updatedOrders;
    overwriteOrders.close();

    cout << "Order for " << productName << " updated in orders file." << endl;
    return true;
}

void placeOrder(const char *productName)
{
    if (!isProductInMenu(productName))
    {
        cout << "Product " << productName << " is unavailable" << endl;
        cout << "Cancelling order..." << endl;
        return;
    }

    if (removeIngredientsFromStorage(productName))
    {
        updateOrderFile(productName);
        updateTurnover(productName, '+');
    }
}

void cancelOrder(const char *productName)
{
    if (!removeOrderFromFile(productName))
    {
        cout << "Error: Unable to remove order. Most likely there was't an order placed." << endl;
        return;
    }

    recoverIngredients(productName);
    updateTurnover(productName, '-');

    cout << "Order for " << productName << " canceled successfully." << endl;
}

void printOrdersWithoutQuantities()
{
    ifstream ordersFile("../data/orders.txt");
    if (!ordersFile)
    {
        cout << "Error: Unable to open orders file!" << endl;
        return;
    }

    cout << "Orders (without quantities):" << endl;
    cout << "-----------------------------" << endl;

    char line[50];
    while (ordersFile.getline(line, sizeof(line)))
    {
        char productName[50];
        sscanf(line, "%s", productName);
        cout << productName << endl;
    }

    ordersFile.close();
}

void sortOrdersAlphabetically(Order orders[], int orderCount)
{
    for (int i = 0; i < orderCount - 1; i++)
    {
        for (int j = 0; j < orderCount - i - 1; j++)
        {
            if (strcmp(orders[j].productName, orders[j + 1].productName) > 0)
            {
                Order temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
}

void printSortedOrdersWithQuantities()
{
    ifstream ordersFile("../data/orders.txt");
    if (!ordersFile)
    {
        cerr << "Error: Unable to open orders file!" << endl;
        return;
    }

    Order orders[MAX_ORDERS];
    int orderCount = 0;

    while (ordersFile >> orders[orderCount].productName >> orders[orderCount].quantity)
    {
        orderCount++;
    }
    ordersFile.close();

    sortOrdersAlphabetically(orders, orderCount);

    cout << "Sorted Orders with Quantities:\n";
    for (int i = 0; i < orderCount; i++)
    {
        cout << orders[i].productName << " " << orders[i].quantity << endl;
    }
}