#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <vector>
#include <string>
#include "Car.h"
#include "Customer.h"
#include "Bank_Customer.h"
#include "BnakSystem.h"

class System {
    public:
        vector<Car> cars;
        vector<Customer> customers;
        BankSystem* bankSystem; 



        void addCustomer() {
            string user_name;
            string user_address;
            string phone_number;

            cout << "\nPlease follow the instructions for the registration..." << endl;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, user_name);

            if (user_name.length() < 3 || user_name.length() > 255) {
                cout << "Name can't be shorter than 3 letters!" << endl;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, user_name);
            }

            cout << "\nEnter your address: ";
            getline(cin, user_address);

            if (user_address.length() < 3 || user_address.length() > 255) {
                cout << "Address can't be shorter than 3 letters!" << endl;
                cout << "\nEnter your address: ";
                getline(cin, user_address);
            }

            cout << "\nEnter your phone number: ";
            cin >> phone_number;

            if (cin.fail() || phone_number.length() != 10 || !all_of(phone_number.begin(), phone_number.end(), ::isdigit)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                cout << "Invalid phone number! It must be exactly 10 digits and contain only numbers." << endl;
                cout << "\nEnter your phone number: ";
                cin >> phone_number;
            }

            customers.push_back(Customer(user_name, user_address, phone_number));
            cout << "\nUser added successfully." << endl;
        }

        void addCar(const string& model, const string& made, int year, double paymentpersecond) {
            cars.push_back(Car(model, made, year, paymentpersecond));
        }

        void displayCars() {
            for (auto& car : cars) {
                if (car.isAvaileble){
                    car.display();
                }
            }
        }

        void displayUsers() {
            for (auto& cust : customers) {
                cust.display();
            }
        }

        void rentCar() {
            string user_name, model, made;
            int year;

            cout << "\nEnter your user name: " << endl;
            cin.ignore();
            getline(cin, user_name);

            cout << "\nEnter the model of the car: " << endl;
            getline(cin, model);

            cout << "\nEnter the made: " << endl;
            getline(cin, made);

            cout << "\nEnter the year: " << endl;
            cin >> year;

            Customer* customer = nullptr;
            for (auto& cust : customers) {
                if (cust.name == user_name) {
                    customer = &cust;
                    break;
                }
            }

            if (!customer) {
                cout << "\nUser not found! Please register first." << endl;
                return;
            }

            Car* car = nullptr;
            for (auto& c : cars) {
                if (c.model == model && c.made == made && c.year == year) {
                    car = &c;
                    break;
                }
            }

            if (!car) {
                cout << "The car with the attributes you entered is not in inventory. "
                     << "Please check out the list of available cars." << endl;
                return;
            }

            customer->rent(*car);
        }

        void return_car() {
            string user_name;

            cout << "\nEnter your user name: " << endl;
            cin.ignore();
            getline(cin, user_name);

            Customer* customer = nullptr;
            for (auto& cust : customers) {
                if (cust.name == user_name) {
                    customer = &cust;
                    break;
                }
            }

            if (!customer) {
                cout << "\nNo car has been rented with this user name." << endl;
                return;
            }

            customer->retunCar();
        }

        void handle_Payment() {
            string user_name;

            cout << "\nEnter your user name: " << endl;
            cin.ignore();
            getline(cin, user_name);

            Customer* customer = nullptr;
            for (auto& cust : customers) {
                if (cust.name == user_name) {
                    customer = &cust;
                    break;
                }
            }

            if (!customer) {
                cout << "\nNo car has been rented with this user name." << endl;
                return;
            }

            customer->handlePayment();
        }

        void Pay_using_bank(BankSystem& bankSystem) {
            string name;
            cout << "Please enter your name: ";
            cin >> name;

            Customer* customer = nullptr;
            for (auto& cust : customers) {
                if (cust.name == name && cust.bill > 0) {
                    Bank_Customer* bank_customer = nullptr;
                    for (auto& bank_cust : bankSystem.bank_customers) {
                        if (bank_cust.name == name) {
                            bank_customer = &bank_cust;
                            bank_cust.deposite -= cust.bill;
                            cust.bill = 0; // Clear the bill
                            cout << "Payment successful! Your current Balance is: $"<<bank_cust.deposite << endl;

                            } else {
                                cout << "Payment failed! Insufficient balance." << endl;
                            }
                            return;
                        
                    }
                }
            }
            cout << "User not found or no outstanding bill." << endl;
        }
};

#endif
