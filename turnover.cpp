#include "functions.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void updateTurnover(const char *productName, const char op) {
    ifstream menuFile("menu.txt");
    if (!menuFile) {
        cout << "Error: Unable to open menu file!" << endl;
        return;
    }

    double productPrice = 0.0;
    char line[100];
    while (menuFile.getline(line, sizeof(line))) {
        char menuProduct[50];
        double price;
        sscanf(line, "%s %lf", menuProduct, &price);
        if (strcmp(menuProduct, productName) == 0) {
            productPrice = price;
            break;
        }
    }
    menuFile.close();

    if (productPrice == 0.0) {
        cout << "Error: Product not found in the menu!" << endl;
        return;
    }

    fstream turnoverFile("turnover_by_day.txt", ios::in | ios::out);
    if (!turnoverFile) {
        cout << "Error: Unable to open turnover file!" << endl;
        return;
    }

    char currentLine[100];
    char lastLine[100] = "";
    streampos lastLinePos = turnoverFile.tellg();
    while (turnoverFile.getline(currentLine, sizeof(currentLine))) {
        strcpy(lastLine, currentLine);
        lastLinePos = turnoverFile.tellg();
    }

    if (strlen(lastLine) == 0) {
        cout << "Error: Turnover file is empty!" << endl;
        turnoverFile.close();
        return;
    }

    char date[50];
    double currentTurnover;
    if (sscanf(lastLine, "%s %lf", date, &currentTurnover) != 2) {
        cout << "Error: Unable to parse the last line of the turnover file!" << endl;
        turnoverFile.close();
        return;
    }

    if (op=='+') {
        currentTurnover += productPrice;
    } else if (op=='-') {
        currentTurnover -= productPrice;
       
    } else {
        cout << "Error: Invalid operation specified!" << endl;
        turnoverFile.close();
        return;
    }

    turnoverFile.clear();
    turnoverFile.seekp(lastLinePos - streampos(strlen(lastLine)) - 1);
    turnoverFile << date << " " << currentTurnover << endl;

    turnoverFile.close();
    cout << "Turnover updated successfully for " << date << ": " << currentTurnover << " BGN" << endl;
}

void showTurnoverForLastDay()
{
    ifstream turnoverFile("turnover_by_day.txt");
    if (!turnoverFile)
    {
        cout << "Error: Unable to open turnover file!" << endl;
        return;
    }

    char lastLine[100] = ""; 
    char currentLine[100];

    while (turnoverFile.getline(currentLine, sizeof(currentLine)))
    {
        strcpy(lastLine, currentLine); 
    }
    //cout<<lastLine<<endl;//

    turnoverFile.close();

    if (strlen(lastLine) == 0)
    {
        cout << "The turnover file is empty or unreadable." << endl;
        return;
    }

    char date[50];
    double turnover;
    if (sscanf(lastLine, "%s %lf", date, &turnover) != 2)
    {
        cout << "Error: Unable to parse the turnover data!" << endl;
        return;
    }
    cout << "Turnover for " << date << ": " << turnover << " BGN" << endl;
}

void addNextDayToTurnoverFile()
{
    ifstream turnoverFile("turnover_by_day.txt");
    if (!turnoverFile)
    {
        cout << "Error: Unable to open turnover file!" << endl;
        return;
    }

    char lastLine[100] = ""; 
    char currentLine[100];

    while (turnoverFile.getline(currentLine, sizeof(currentLine)))
    {
        strcpy(lastLine, currentLine); 
    }

    turnoverFile.close();

    if (strlen(lastLine) == 0)
    {
        cout << "The turnover file is empty or unreadable." << endl;
        return;
    }

    char date[50];
    if (sscanf(lastLine, "%s", date) != 1)
    {
        cout << "Error: Unable to parse the last date!" << endl;
        return;
    }

    int day, month, year;
    sscanf(date, "%d.%d.%d", &day, &month, &year);

    getNextDay(day, month, year);

    char newDate[50];
    snprintf(newDate, sizeof(newDate), "%02d.%02d.%04d", day, month, year);

    ofstream turnoverFileOut("turnover_by_day.txt", ios::app);
    if (!turnoverFileOut)
    {
        cout << "Error: Unable to open turnover file for appending!" << endl;
        return;
    }
    turnoverFileOut << newDate << " 0.0" << endl;
    turnoverFileOut.close();

    cout << "Added new day (" << newDate << ") with turnover 0.0 to the turnover file." << endl;
}

void printAllTurnovers() {
    ifstream turnoverFile("turnover_by_day.txt");
    if (!turnoverFile) {
        cout << "Error: Unable to open turnover file!" << endl;
        return;
    }

    char line[100];
    while (turnoverFile.getline(line, sizeof(line))) {
        char date[50];
        double turnover;

        if (sscanf(line, "%s %lf", date, &turnover) == 2) {
            cout << date << " " << turnover << " BGN" << endl;
        } else {
            cout << "Error: Unable to parse line: " << line << endl;
        }
    }

    turnoverFile.close();
}