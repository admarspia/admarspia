#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

struct Car {
    string model;
    string made;
    int year;
    double paymentPerSecond;
    bool isAvailable;
};

struct Customer {
    string name;
    string address;
    string phone;
    bool hasRentedCar;
    Car* rentedCar;
    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point endTime;
};

void addCar(vector<Car>& cars, const string& model, const string& made, int year, double paymentPerSecond);
void displayCars(const vector<Car>& cars);
void addUser(vector<Customer>& customers);
void rentCar(vector<Car>& cars, vector<Customer>& customers);
void returnCar(vector<Customer>& customers);
void handlePayment(vector<Customer>& customers);

int main() {
    vector<Car> cars;
    vector<Customer> customers;

    addCar(cars, "Toyota Corolla", "Toyota", 2022, 0.01);
    addCar(cars, "Ford Mustang", "Ford", 2021, 0.01);
    addCar(cars, "Honda Civic", "Honda", 2020, 0.02);
    addCar(cars, "Chevrolet Camaro", "Chevrolet", 2019, 0.03);

    while (true) {
        cout << "\n-----------------------------------" << endl;
        cout << "      Welcome to Car Rental System" << endl;
        cout << "-----------------------------------" << endl;
        cout << "1. Register a New User" << endl;
        cout << "2. View Available Cars" << endl;
        cout << "3. Rent a Car" << endl;
        cout << "4. Return a Car" << endl;
        cout << "5. Check Payment Details" << endl;
        cout << "6. Exit" << endl;
        cout << "-----------------------------------" << endl;
        cout << "Enter your choice (1-6): ";

        int choice;
        cin >> choice;

    
        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\nInvalid input. Please enter a number between 1 and 6.\n" << endl;
            continue;
        }

        switch (choice) {
            case 1:
                addUser(customers);
                break;
            case 2:
                displayCars(cars);
                break;
            case 3:
                rentCar(cars, customers);
                break;
            case 4:
                returnCar(customers);
                break;
            case 5:
                handlePayment(customers);
                break;
            case 6:
                cout << "\nThank you for using the Car Rental System. Have a great day!\n" << endl;
                return 0;
            default:
                cout << "\nAn unexpected error occurred. Please try again.\n" << endl;
                break;
        }
    }
    return 0;
}


void addCar(vector<Car>& cars, const string& model, const string& made, int year, double paymentPerSecond) {
    cars.push_back({model, made, year, paymentPerSecond, true});
}

void displayCars(const vector<Car>& cars) {
    cout << "\nAvailable Cars:\n";
    cout << left << setw(15) << "Made" << setw(15) << "Model" << setw(10) << "Year" << setw(10) << "Rate ($/s)" << endl;
    for (const auto& car : cars) {
        if (car.isAvailable) {
            cout << left << setw(15) << car.made << setw(15) << car.model 
                 << setw(10) << car.year << setw(10) << car.paymentPerSecond << endl;
        }
    }
}

void addUser(vector<Customer>& customers) {
    string name, address, phone;
    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your address: ";
    getline(cin, address);
    cout << "Enter your phone number: ";
    cin >> phone;

    Customer* customer = nullptr;
    for (auto& cust : customers) {
        if (cust.phone == phone) {
            customer = &cust;
            break;
        }
    }

    if (!customer) {
        customers.push_back({name, address, phone, false, nullptr});
        cout << "User registered successfully.\n";        return;
    }
    else{
        cout << "Acount already in use please check out your name and phone number." << endl;
    }

    customers.push_back({name, address, phone, false, nullptr});
    cout << "User registered successfully.\n";
}

void rentCar(vector<Car>& cars, vector<Customer>& customers) {
    string userName, model, made;
    int year;

    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, userName);

    Customer* customer = nullptr;
    for (auto& cust : customers) {
        if (cust.name == userName) {
            customer = &cust;
            break;
        }
    }

    if (!customer) {
        cout << "User not found! Please register first.\n";
        return;
    }

    cout << "Enter the car make: ";
    getline(cin, made);
    cout << "Enter the car model: ";
    getline(cin, model);
    cout << "Enter the car year: ";
    cin >> year;

    Car* car = nullptr;
    for (auto& c : cars) {
        if (c.made == made && c.model == model && c.year == year && c.isAvailable) {
            car = &c;
            break;
        }
    }
    
    if (!car) {
        cout << "Car not available or not found.\n";
        return;
    }

    customer->rentedCar = car;
    customer->hasRentedCar = true;
    customer->startTime = high_resolution_clock::now();
    car->isAvailable = false;
    cout << "Car rented successfully.\n";
}

void returnCar(vector<Customer>& customers) {
    string userName;

    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, userName);

    Customer* customer = nullptr;
    for (auto& cust : customers) {
        if (cust.name == userName && cust.hasRentedCar) {
            customer = &cust;
            break;
        }
    }

    if (!customer) {
        cout << "No active rental found for this user.\n";
        return;
    }

    customer->endTime = high_resolution_clock::now();
    customer->rentedCar->isAvailable = true;
    customer->hasRentedCar = false;
    cout << "Car returned successfully.\n";
}

void handlePayment(vector<Customer>& customers) {
    string userName;

    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, userName);

    Customer* customer = nullptr;
    for (auto& cust : customers) {
        if (cust.name == userName && !cust.hasRentedCar && cust.rentedCar != nullptr) {
            customer = &cust;
            break;
        }
    }

    if (!customer) {
        cout << "No payment due for this user.\n";
        return;
    }

    auto duration = duration_cast<seconds>(customer->endTime - customer->startTime);
    double totalPayment = duration.count() * customer->rentedCar->paymentPerSecond;
    cout << "Total time rented: " << duration.count() << " seconds.\n";
    cout << "Total payment: $" << totalPayment << "\n";

    customer->rentedCar = nullptr; 
}
