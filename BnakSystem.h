#ifndef BANK_SYSTEM
#define BANK_SYSTEM
#include <iostream>
#include <string>
#include <vector>
#include <ctime> 
#include <limits>
#include "Customer.h"
#include "Bank_Customer.h"
#include "System.h"
using namespace std;

class BankSystem {
public:
    vector<Bank_Customer> bank_customers;

    void validate(string& name) {
        while (name.length() < 3) {
            cout << "Name cannot be less than 3 characters. Please enter your name again: ";
            getline(cin, name);
        }
    }

    void addUser() {
        int acount_num = rand();
        string name;
        int phone_num;
        double init_deposite;

        cout << "Enter user name: ";
        cin.ignore();
        getline(cin, name);
        validate(name);

        cout << "\nEnter phone number: ";
        cin >> phone_num;

        cout << "\nEnter amount for the account to start with: ";
        cin >> init_deposite;

        cout << "Your account has been created with an initial amount of: $" << init_deposite
             << ". Your account number is " << acount_num << endl;

        bank_customers.push_back(Bank_Customer(name, acount_num, phone_num, init_deposite));
    }

    void displayUsers() {
        for (auto& customer : bank_customers) {
            customer.displayUser();
        }
    }

    void deposite() {
        string name;
        int acount_num;
        double amount;

        cout << "Enter user name: ";
        cin.ignore();
        getline(cin, name);
        validate(name);

        cout << "Enter account number: ";
        cin >> acount_num;

        cout << "Enter the amount you want to deposit: ";
        cin >> amount;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input for amount!" << endl;
            return;
        }

        for (auto& cust : bank_customers) {
            if (cust.name == name && cust.acount_num == acount_num) {
                cust.deposite += amount;
                cout << cust.name << "! Your amount has been deposited. Your current balance is: $"
                     << cust.deposite << endl;
                return;
            }
        }

        cout << "Customer not found! Please check the 'user name' or 'account number'!" << endl;
    }

    void withdraw() {
        string name;
        int acount_num;
        double amount;

        cout << "Enter user name: ";
        cin.ignore();
        getline(cin, name);
        validate(name);

        cout << "Enter account number: ";
        cin >> acount_num;

        cout << "Enter the amount you want to withdraw: ";
        cin >> amount;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input for amount!" << endl;
            return;
        }

        for (auto& cust : bank_customers) {
            if (cust.name == name && cust.acount_num == acount_num) {
                if (cust.deposite >= amount) {
                    cust.deposite -= amount;
                    cout << cust.name << "! Your withdrawal of " << amount
                         << " was successful. Your current balance is: $" << cust.deposite << endl;
                } else {
                    cout << "Insufficient balance!" << endl;
                }
                return;
            }
        }

        cout << "Customer not found!" << endl;
    }

    void showBalance() {
        string name;
        int acount_num;

        cout << "Enter user name: ";
        cin.ignore();
        getline(cin, name);
        validate(name);

        cout << "Enter account number: ";
        cin >> acount_num;

        for (auto& cust : bank_customers) {
            if (cust.name == name && cust.acount_num == acount_num) {
                cout << cust.name << "! Your current balance is: " << cust.deposite << endl;
                return;
            }
        }

        cout << "Customer not found!" << endl;
    }

    void Transfer() {
        string name;
        int acount_num, sendTo;
        double amount;

        cout << "Enter user name: ";
        cin.ignore();
        getline(cin, name);
        validate(name);

        cout << "Enter your account number: ";
        cin >> acount_num;

        cout << "Enter the account number to transfer to: ";
        cin >> sendTo;

        cout << "Enter the amount to transfer: ";
        cin >> amount;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input for amount!" << endl;
            return;
        }

        Bank_Customer *sender = nullptr, *receiver = nullptr;

        for (auto& cust : bank_customers) {
            if (cust.name == name && cust.acount_num == acount_num) {
                sender = &cust;
            }
            if (cust.acount_num == sendTo) {
                receiver = &cust;
            }
        }

        if (!sender) {
            cout << "Sender account not found!" << endl;
            return;
        }
        if (!receiver) {
            cout << "Receiver account not found!" << endl;
            return;
        }
        if (sender->deposite < amount) {
            cout << "Insufficient balance for transfer!" << endl;
            return;
        }

        sender->deposite -= amount;
        receiver->deposite += amount;
        cout << "Successfully transferred " << amount << " to " << receiver->name << endl;
    }
};



#endif
