#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <algorithm>
#include <cctype> 
#include <chrono>
#include "Car.h"

#include <iostream>
#include <string>
using namespace std;
using namespace std::chrono;

class Customer {
    public:
        string name;
        string address;
        bool rentedcar;
        string phone;
        double bill;
        Car *theRentedCar;
        high_resolution_clock::time_point startTime;
        high_resolution_clock::time_point endTime;

        Customer(string n, string add, string p, int b = 0)
            : name(n), address(add), phone(p), rentedcar(false),bill(b), theRentedCar(nullptr) {}

        void display() {
            cout << "( name: " << name << ", address: " << address << ", phone number: " << phone << " )" << endl;
        }

        void rent(Car& car) {
            if (car.isAvaileble) {
                rentedcar = true;
                startTime = high_resolution_clock::now();
                theRentedCar = &car;
                car.isAvaileble = false;
                cout << name << " you have successfully rented the car " << car.model 
                     << ". Thank you for visiting our site." << endl;
            }
            else{
                cout << "This Car is not availeble at this time " << endl;
            }
        }

        void retunCar() {
            if (rentedcar) {
                rentedcar = false;
                endTime = high_resolution_clock::now();
                theRentedCar->isAvaileble = true;
                cout << name << " you have successfully returned the car " << theRentedCar->model 
                     << ". Thank you for visiting our site." << endl;
            }
        }

        void handlePayment() {
            auto duration = duration_cast<seconds>(endTime - startTime);
            cout << "Duration: " << duration.count() << " seconds." << endl;
            bill = duration.count() * theRentedCar->paymentpersecond;
            cout << "The total payment is: $" << bill << endl;
            theRentedCar = nullptr;
        }
        
};

#endif
