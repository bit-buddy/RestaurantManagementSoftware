#include <iostream>
#include <fstream>
#include <cstring>
#include "../include/storage.h"

using namespace std;

Ingredient storage[MAX_INGREDIENTS];
int storageSize = 0;

struct ProductIngredients
{
    const char *productName;
    Ingredient ingredients[MAX_INGREDIENTS];
    int numIngredients;
};

ProductIngredients productData[] = {
    {"Burger", {{"Buns", 200}, {"Beef", 150}, {"Cheese", 100}}, 3},
    {"Pizza", {{"Dough", 400}, {"Tomato", 200}, {"Cheese", 300}}, 3},
    {"Pasta", {{"Pasta", 500}, {"Tomato", 200}}, 2},
    {"Salad", {{"Lettuce", 50}, {"Tomato", 200}, {"Cucumber", 100}}, 3},
    {"Sandwich", {{"Bread", 100}, {"Cheese", 100}, {"Tomato", 100}}, 3},
    {"Cheesecake", {{"Cheese", 200}, {"Crust", 100}}, 2}};

bool readStorage(Ingredient storage[], int &storageSize)
{
    ifstream storageFile("../data/storage.txt");
    if (!storageFile)
    {
        cout << "Error opening storage file!" << endl;
        return false;
    }

    storageSize = 0;
    char line[MAX_LEN];
    while (storageFile.getline(line, MAX_LEN))
    {
        sscanf(line, "%s %d", storage[storageSize].name, &storage[storageSize].quantity);
        storageSize++;
    }

    storageFile.close();
    return true;
}

void writeStorage(Ingredient storage[], int storageSize)
{
    ofstream storageFile("../data/storage.txt");
    if (!storageFile)
    {
        cerr << "Error opening storage file to write!" << endl;
        return;
    }

    for (int i = 0; i < storageSize; i++)
    {
        storageFile << storage[i].name << " " << storage[i].quantity << endl;
    }

    storageFile.close();
}

bool removeIngredientsFromStorage(const char *productName)
{
    if (!readStorage(storage, storageSize))
    {
        return false;
    }

    Ingredient *ingredientsToRemove = nullptr;
    int numIngredients = 0;
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(productName, productData[i].productName) == 0)
        {
            ingredientsToRemove = productData[i].ingredients;
            numIngredients = productData[i].numIngredients;
            break;
        }
    }

    for (int i = 0; i < numIngredients; i++)
    {
        for (int j = 0; j < storageSize; j++)
        {
            if (strcmp(storage[j].name, ingredientsToRemove[i].name) == 0)
            {
                if (storage[j].quantity >= ingredientsToRemove[i].quantity)
                {
                    storage[j].quantity -= ingredientsToRemove[i].quantity;
                    break;
                }
                else
                {
                    cout << "Not enough " << ingredientsToRemove[i].name << " in stock!" << endl;
                    cout << "Cancelling order..." << endl;
                    return false;
                }
            }
        }
    }

    writeStorage(storage, storageSize);
    cout << "Ingredients for " << productName << " have been successfully removed from storage." << endl;
    return true;
}

void recoverIngredients(const char *productName)
{
    Ingredient storage[MAX_INGREDIENTS];
    int storageSize = 0;

    if (!readStorage(storage, storageSize))
    {
        cerr << "Error: Unable to process storage!" << endl;
        return;
    }

    Ingredient *ingredientsToRevert = nullptr;
    int numIngredients = 0;
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(productName, productData[i].productName) == 0)
        {
            ingredientsToRevert = productData[i].ingredients;
            numIngredients = productData[i].numIngredients;
            break;
        }
    }

    if (ingredientsToRevert == nullptr)
    {
        cerr << "Error: Product data not found in storage recovery!" << endl;
        return;
    }

    for (int i = 0; i < numIngredients; i++)
    {
        for (int j = 0; j < storageSize; j++)
        {
            if (strcmp(storage[j].name, ingredientsToRevert[i].name) == 0)
            {
                storage[j].quantity += ingredientsToRevert[i].quantity;
                break;
            }
        }
    }
    writeStorage(storage, storageSize);

    cout << "Ingredients recovered for " << productName << "." << endl;
}

void printStorageWithQuantities()
{
    ifstream storageFile("../data/storage.txt");
    if (!storageFile)
    {
        cout << "Error: Unable to open storage file!" << endl;
        return;
    }

    char itemName[50];
    int quantity;

    cout << "Storage Items with Quantities:\n";
    cout << "-----------------------------\n";

    while (storageFile >> itemName >> quantity)
    {
        cout << itemName << " " << quantity << "g." << endl;
    }

    storageFile.close();
}

void removeProductFromStorage(const char *productName)
{
    ifstream storageFile("../data/storage.txt");
    if (!storageFile)
    {
        cerr << "Error: Unable to open storage file!" << endl;
        return;
    }

    char tempContent[5000] = "";
    char itemName[50];
    int quantity;
    bool ingredientFound = false;

    while (storageFile >> itemName >> quantity)
    {
        if (strcmp(itemName, productName) != 0)
        {
            char line[100];
            snprintf(line, sizeof(line), "%s %d\n", itemName, quantity);
            strcat(tempContent, line);
        }
        else
        {
            ingredientFound = true;
        }
    }
    storageFile.close();

    if (!ingredientFound)
    {
        cout << "Ingredient '" << productName << " not found in storage." << endl;
        return;
    }

    ofstream storageOutput("../data/storage.txt");
    if (!storageOutput)
    {
        cout << "Error: Unable to open storage file for writing!" << endl;
        return;
    }
    storageOutput << tempContent;
    storageOutput.close();

    cout << "Ingredient '" << productName << "' has been removed from storage." << endl;
}

void addProductToStorage(const char *productName, int quantity)
{
    ifstream storageFile("../data/storage.txt");
    if (!storageFile)
    {
        cout << "Error: Unable to open storage file!" << endl;
        return;
    }

    char tempContent[5000] = "";
    char itemName[50];
    int existingQuantity;
    bool productFound = false;

    while (storageFile >> itemName >> existingQuantity)
    {
        if (strcmp(itemName, productName) == 0)
        {
            existingQuantity += quantity;
            productFound = true;
        }
        char line[100];
        snprintf(line, sizeof(line), "%s %d\n", itemName, existingQuantity);
        strcat(tempContent, line);
    }
    storageFile.close();

    if (!productFound)
    {
        char newProductLine[100];
        snprintf(newProductLine, sizeof(newProductLine), "%s %d\n", productName, quantity);
        strcat(tempContent, newProductLine);
    }

    ofstream storageOutput("../data/storage.txt");
    if (!storageOutput)
    {
        cerr << "Error: Unable to open storage file for writing!" << endl;
        return;
    }
    storageOutput << tempContent;
    storageOutput.close();

    cout << "Product '" << productName << "' has been added/updated in storage with quantity: " << quantity << "g." << endl;
}