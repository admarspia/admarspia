#ifndef BANK_CUSTOMER
#define BANK_CUSTOMER

#include <iostream>
#include <string>
using namespace std;

class Bank_Customer {
public:
    string name;
    int acount_num;
    int phone_num;
    double deposite;

    Bank_Customer(string n, int acount_n, int phone, double init_deposite)
        : name(n), acount_num(acount_n), phone_num(phone), deposite(init_deposite) {}

    void displayUser() {
        cout << "neme: " << name << "  acount_num: " << acount_num << "balance: " << deposite << endl;
    }
};

#endif