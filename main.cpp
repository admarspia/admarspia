#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype> 
#include <chrono>
using namespace std;
using namespace std::chrono;

class Car {
    public:
        string model, made;
        double paymentpersecond;
        bool isAvaileble;
        int year;

        Car(string m, string mod, int y, double paymentpersec)
            : model(m), made(mod), year(y), paymentpersecond(paymentpersec) {}

        void display() {
            cout << "( made: " << made << "    model: " << model << "    year: " << year << " )" << endl;
        }
};

class Customer {
    public:
        string name;
        string address;
        bool rentedcar;
        string phone;
        Car* theRentedCar;
        high_resolution_clock::time_point startTime;
        high_resolution_clock::time_point endTime;

        Customer(string n, string add, string p)
            : name(n), address(add), phone(p), rentedcar(false), theRentedCar(nullptr) {}

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
            double payment;
            auto duration = duration_cast<seconds>(endTime - startTime);
            cout << "Duration: " << duration.count() << " seconds." << endl;
            payment = duration.count() * theRentedCar->paymentpersecond;
            cout << "The total payment is: $" << payment << endl;
            theRentedCar = nullptr;
        }
};
class System {
    public:
        vector<Car> cars;
        vector<Customer> customers;

        void addUser() {
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
                cin.clear();  // Clear the fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
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
                car.display();
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

            cout << "\nEnter the made of the car: " << endl;
            getline(cin, model);

            cout << "\nEnter the model: " << endl;
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
};
int main() {
    System system;
    system.addCar("Toyota Corolla", "Toyota", 2022, 0.01);
    system.addCar("Ford Mustang", "Ford", 20210, 0.01);
    system.addCar("Honda Civic", "Honda", 2020, 0.02);
    system.addCar("Chevrolet Camaro", "Chevrolet", 2019, 0.03);
    system.addCar("Tesla Model 3", "Tesla", 2023, 0.01);
    system.addCar("Nissan Altima", "Nissan", 2018, 0.01);
    system.addCar("BMW 3 Series", "BMW", 2022, 0.06);
    system.addCar("Mercedes-Benz C-Class", "Mercedes-Benz", 2023, 0.01);
    system.addCar("Audi A4", "Audi", 2021, 0.01);
    system.addCar("Volkswagen Passat", "Volkswagen", 2020, 0.04);

    int customerChoice;
    string next_do;

    while (true) {
        cout << "\n____*** Welcome to the Car Rental System ***____" << endl;
        cout << "Please enter: \n'1' to go to the registration page\n"
             << "'2' To see the list of available Cars\n"
             << "'3' To rent a Car\n"
             << "'4' To return the car you rented before\n"
             << "'5' To check the payment amount\n"
             << "'6' To exit the application" << endl;

        cin >> customerChoice;

        // Validate input
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            cin.clear();  // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            continue;
        }

        switch (customerChoice) {
            case 1:
                system.addUser();
                cout << "\nEnter 'y' to go to the main menu or anything else to exit: ";
                cin >> next_do;
                if (next_do != "y") {
                    return 0;
                }
                break;

            case 2:
                system.displayCars();
                cout << "\nEnter 'y' to go to the main menu or anything else to exit: ";
                cin >> next_do;
                if (next_do != "y") {
                    cout << "Thank you for visiting our site\n... closing the application." << endl;
                    return 0;
                }
                break;

            case 3:
                system.rentCar();
                cout << "\nEnter 'y' to go to the main menu or anything else to exit: ";
                cin >> next_do;
                if (next_do != "y") {
                    cout << "Thank you for visiting our site\n... closing the application." << endl;
                    return 0;
                }
                break;

            case 4:
                system.return_car();
                cout << "\nEnter 'y' to go to the main menu or anything else to exit: ";
                cin >> next_do;
                if (next_do != "y") {
                    cout << "Thank you for visiting our site\n... closing the application." << endl;
                    return 0;
                }
                break;

            case 5:
                system.handle_Payment();
                cout << "\nEnter 'y' to go to the main menu or anything else to exit: ";
                cin >> next_do;
                if (next_do != "y") {
                    cout << "Thank you for visiting our site\n... closing the application." << endl;
                    return 0;
                }
                break;

            case 6:
                cout << "Thank you for visiting our site\n... closing the application." << endl;
                return 0;

            default:
                cout << "\nInvalid choice. Please select a valid option." << endl;
                break;
        }
    }
    return 0;
}
