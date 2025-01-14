#include <iostream>
#include "functions.h"
#include "order.cpp"
#include "menu.cpp"
#include "storage.cpp"
#include "turnover.cpp"
#include "calendar.cpp"

using namespace std;

void chooseUserType()
{
    cout << "Welcome to the Restaurant Management System!" << endl;

    while (true)
    {
        cout << "\nAre you a (1) Waiter or (2) Manager? Enter 0 to Exit: ";
        int userType;
        cin >> userType;

        if (cin.fail() || (userType != 0 && userType != 1 && userType != 2))
        {
            cin.clear();             // Clear the error flag
            cin.ignore(10000, '\n'); // Discard invalid input
            cout << "Invalid choice! Please enter 0, 1, or 2." << endl;
            continue;
        }

        if (userType == 0)
        {
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        }
        else if (userType == 1)
        {
            cout << "\nYou are logged in as a Waiter." << endl;
            waiterMenu();
        }
        else if (userType == 2)
        {
            cout << "\nYou are logged in as a Manager." << endl;
            managerMenu();
        }
    }
}
void waiterMenu()
{
    const int MAX_SIZE = 100;
    int waiterChoice;
    do
    {
        cout << "\n \
        Waiter Menu - Select an Option:\n";
        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. Cancel Order\n";
        cout << "4. View Past Orders\n";
        cout << "5. View Sorted Past Orders and Counts\n";
        cout << "6. View Turnover for the Day\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        cin >> waiterChoice;

        switch (waiterChoice)
        {
        case 1:
            printMenuItems();
            break;
        case 2:
            char input[MAX_LEN];
            cout << "Enter the desired order:\n";
            cin>>input;
            cout<<"You entered: "<<input<<endl;
            placeOrder(input);

            break;
        case 3:
            // Call function to cancel order
            break;
        case 4:
            // Call function to view past orders
            break;
        case 5:
            // Call function to view sorted past orders and counts
            break;
        case 6:
            showTurnoverForLastDay();
            break;
        case 0:
            cout << "Returning to main menu..." << endl;
            return;
        default:
            cout << "Invalid option! Please try again." << endl;
        }
    } while (waiterChoice != 0);
}
void managerMenu()
{
    const int MAX_SIZE = 100;
    int managerChoice;
    do
    {
        cout << "\nManager Menu:" << endl;
        cout << "1. View menu" << endl;
        cout << "2. Place an order" << endl;
        cout << "3. Cancel an order" << endl;
        cout << "4. View sorted past orders" << endl;
        cout << "5. View past orders" << endl;
        cout << "6. View stock" << endl;
        cout << "7. Remove a product from storage" << endl;
        cout << "8. Add a product to storage" << endl;
        cout << "9. View turnover for today" << endl;
        cout << "10. Get today's report" << endl;
        cout << "11. View all turnovers" << endl;
        cout << "12. Add new product to menu" << endl;
        cout << "13. Remove product from menu" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> managerChoice;

        switch (managerChoice)
        {
        case 1:
            printMenuItems();
            break;
        case 2:
        {
            char productName[50];
            cout << "Enter product name to order: ";
            cin >> productName;
            placeOrder(productName);
        }
        break;
        case 3:
        {
            char productName[50];
            cout << "Enter product name to cancel: ";
            cin >> productName;
            cancelOrder(productName);
        }
        break;
        case 4:
            printSortedOrdersWithQuantities();
            break;
        case 5:
            printOrdersWithoutQuantities();
            break;
        case 6:
            printStorageWithQuantities();
            break;
        case 7:
        {
            char productName[50];
            cout << "Enter product name to remove from storage: ";
            cin >> productName;
            removeProductFromStorage(productName);
        }
        break;
        case 8:
        {
            char productName[50];
            int quantity;
            cout << "Enter product name to add to storage: ";
            cin >> productName;
            cout << "Enter quantity to add: ";
            cin >> quantity;
            addProductToStorage(productName, quantity);
        }
        break;
        case 9:
            showTurnoverForLastDay();
            break;
        case 10:
            addNextDayToTurnoverFile();
            break;
        case 12:
        {
            char productName[50];
            double price;
            cout << "Enter product name to add to menu: ";
            cin >> productName;
            cout << "Enter product price: ";
            cin >> price;
            addProductToMenu(productName, price);
        }
        break;
        case 13:
        {
            char productName[50];
            cout << "Enter product name to remove from menu: ";
            cin >> productName;
            removeProductFromMenu(productName);
        }
        break;
        case 0:
            cout << "Exiting Manager Menu..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
    } while (managerChoice != 0);
}

int main()
{
    chooseUserType();
    return 0;
}
