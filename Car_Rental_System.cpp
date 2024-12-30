#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip> // For alignment
#include "Car.h"
#include "Customer.h"
#include "System.h"
#include "Bank_Customer.h"
#include "BnakSystem.h"
using namespace std;

// Function for color output
void setColor(int colorCode) {
    cout << "\033[" << colorCode << "m";
}

// Function to display the header
void displayHeader(const string& title) {
    setColor(34); // Blue
    cout << "========================================================================================" << endl;
    cout << R"(

          ███████████████╗   ████████████╗     ███████╗███████║  ██████╗   ██████╗    █████████████║
          ███╔══███╔═══██║   ███╔════════╝     ██╔══██║██║  ██║ ██╔═══██╗ ██╔═══██╗   ██╔══███╔══██║
          ███║  ███║   ██║   ███║ ███║ ██║     ╚═╝  ██║██║  ╚═╝ ██║   ██║ ██║   ██║   ╚═╝  ███║  ╚═╝
          ███║  ███║   ██║   ███╔════════╝          ██║██║      ██║   ██║ ██║   ██║        ███║
          ███║  ███║   ██║   ███║ ███████║     ║██████║███████║ ╚██████╔╝ ╚██████╔╝        ███║
          ╚══╝  ╚══╝   ╚═╝   ╚══╝ ═══════╝     ╚══════╝╚══════╝  ╚═════╝   ╚═════╝         ╚══╝
                                                           
  )" << endl;

    setColor(33); // Yellow
    cout << setw(50) << title << endl;
    setColor(34); // Blue
    cout << "=========================================================================================" << endl;
    setColor(0);  // Reset
}

// Function to display the main menu
void displayMainMenu() {
    displayHeader("WELCOME TO MEXOOT");
    cout << "\n"
         << "Please select an option below:\n\n";
    setColor(32); // Green
    cout << "  1. Bank Management System\n";
    cout << "  2. Car Rental System\n";
    cout << "  3. Exit Application\n";
    setColor(0);  // Reset
    cout << "\nEnter your choice: ";
}


// Bank management menu
int bank_manegmant_system(BankSystem& bankSystem) {
    int cust_choice;

    while (true) {
        displayHeader("BANK MANAGEMENT SYSTEM");
        cout << "\nManage your bank account:\n\n";
        cout << "  1. Add a New User\n";
        cout << "  2. Deposit Money\n";
        cout << "  3. Display All Users\n";
        cout << "  4. Make a Withdrawal\n";
        cout << "  5. Transfer Funds\n";
        cout << "  6. Check Balance\n";
        cout << "  7. Return to Main Menu\n";
        cout << "\nEnter your choice: ";

        cin >> cust_choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 7." << endl;
            continue;
        }

        switch (cust_choice) {
            case 1:
                bankSystem.addUser();
                break;
            case 2:
                bankSystem.deposite();
                break;
            case 3:
                bankSystem.displayUsers();
                break;
            case 4:
                bankSystem.withdraw();
                break;
            case 5:
                bankSystem.Transfer();
                break;
            case 6:
                bankSystem.showBalance();
                break;
            case 7:
                cout << "Returning to the main menu.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

// Car rental menu
int car_rental(BankSystem& bankSystem) {
    System system;
// Pre-load some cars
    system.addCar("Toyota Corolla", "Toyota", 2022, 0.01);
    system.addCar("Ford Mustang", "Ford", 2021, 0.01);
    system.addCar("Honda Civic", "Honda", 2020, 0.02);
    system.addCar("Chevrolet Camaro", "Chevrolet", 2019, 0.03);
    system.addCar("Tesla Model 3", "Tesla", 2023, 0.01);
    system.addCar("Nissan Altima", "Nissan", 2018, 0.01);
    system.addCar("BMW 3 Series", "BMW", 2022, 0.06);
    system.addCar("Mercedes-Benz C-Class", "Mercedes-Benz", 2023, 0.01);
    system.addCar("Audi A4", "Audi", 2021, 0.01);
    system.addCar("Volkswagen Passat", "Volkswagen", 2020, 0.04);
    int customerChoice;
    while (true) {
        cout << "\n*** Welcome to the Car Rental System ***" << endl;
        cout << "Please enter: \n"
             << "1. Register\n"
             << "2. View Cars\n"
             << "3. Rent a Car\n"
             << "4. Return Car\n"
             << "5. Handle Payment\n"
             << "6. Pay using Bank\n"
             << "7. Return to Main Menu\n";

        cin >> customerChoice;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (customerChoice) {
            case 1:
                system.addCustomer();
                break;

            case 2:
                system.displayCars();
                break;

            case 3:
                system.rentCar();
                break;

            case 4:
                system.return_car();
                break;

            case 5:
                system.handle_Payment();
                break;

            case 6:
                system.Pay_using_bank(bankSystem); // Pass BankSystem for payments
                break;

            case 7:
                cout << "Returning to the main menu." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
int main() {
    int choice;

    while (true) {
        // Display main menu
        displayMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input! Please enter a valid number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                while (true) {
                    displayBankManagementMenu();
                    cin >> choice;
                    if (choice == 8) break; // Return to main menu
                }
                break;

            case 2:
                while (true) {
                    displayCarRentalMenu();
                    cin >> choice;
                    if (choice == 7) break; // Return to main menu
                }
                break;

            case 3:
                cout << "\nThank you for using MEXOOT. Goodbye!" << endl;
                return 0;

            default:
                cout << "\nInvalid choice! Please select 1, 2, or 3." << endl;
        }
    }

    return 0;
}


