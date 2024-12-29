#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
using namespace std;

class Car {
    public:
        string model, made;
        double paymentpersecond;
        bool isAvaileble = true;
        int year;

        Car(string mod, string m, int y, double paymentpersec)
            : model(mod), made(m), year(y), paymentpersecond(paymentpersec) {}

        void display() {
            cout << "( made: " << made << "    model: " << model << "    year: " << year << " )" << endl;
        }
};

#endif