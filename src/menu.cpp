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

* <file with definitions of the functionalities within the menu.h file>
*
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include "../include/menu.h"

using namespace std;

void printMenuItems() {
    ifstream inFile("../data/menu.txt");

    if (!inFile) {
        cout << "Error: Unable to open file!" << endl;
        return;
    }

    char itemName[MAX_LEN];
    double price;

    cout << "Menu Items:\n";
    cout << "-----------------------\n";

    int counter = 1;
    while (inFile >> itemName >> price) {
        cout << setw(3) << counter++ << ". " << itemName << endl;
    }

    inFile.close();
}

void addProductToMenu(const char* productName, double productPrice) {
    ofstream menuFile("../data/menu.txt", ios::app);
    if (!menuFile) {
        cout << "Error: Unable to open menu file!" << endl;
        return;
    }

    menuFile << productName << " " << productPrice << endl;

    menuFile.close();
    cout << "Product \"" << productName << "\" with price " << productPrice << " has been added to the menu!" << endl;
}

void removeProductFromMenu(const char* productName) {
    ifstream menuFile("../data/menu.txt");
    if (!menuFile) {
        cout << "Error: Unable to open menu file!" << endl;
        return;
    }

    ofstream tempFile("../data/temp_menu.txt");
    if (!tempFile) {
        cout << "Error: Unable to open temporary file!" << endl;
        menuFile.close();
        return;
    }

    char line[100];
    bool productFound = false;

    while (menuFile.getline(line, sizeof(line))) {
        char menuProduct[50];
        double price;

        if (sscanf(line, "%s %lf", menuProduct, &price) == 2) {
            if (strcmp(menuProduct, productName) == 0) {
                productFound = true;
                continue; 
            }
        }

        tempFile << line << endl;
    }

    menuFile.close();
    tempFile.close();

    if (productFound) {
        remove("../data/menu.txt"); 
        rename("../data/temp_menu.txt", "../data/menu.txt"); 
        cout << "Product \"" << productName << "\" has been removed from the menu." << endl;
    } else {
        remove("../data/temp_menu.txt"); 
        cout << "Product \"" << productName << "\" not found in the menu." << endl;
    }
}
