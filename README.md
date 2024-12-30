readme
# Car Rental System

A C++ project that simulates a **Car Rental System** integrated with a **Banking System**. This system allows customers to rent cars and pay their bills using their bank accounts. It demonstrates object-oriented programming principles, such as encapsulation, inheritance, and polymorphism.

---

## Features

### **Customer Module**
- Register a new customer.
- View available cars for rent.
- Rent a car and generate a bill.
- Check outstanding bills.

### **Bank Module**
- Register a bank customer.
- View account details and balance.
- Pay car rental bills directly from the bank account.

### **Admin Module**
- Add new cars to the system.
- Manage car availability.
- View all registered customers.

---

## Project Structure

- **Classes**:
  - `Customer`: Represents a customer who rents cars.
  - `Car`: Represents a car available for rent.
  - `System`: Manages all customers and cars.
  - `Bank_Customer`: Represents a customer with a bank account.
  - `BankSystem`: Manages all bank customers and payment transactions.

- **Core Functionalities**:
  - `rent_car()`: Allows a customer to rent a car.
  - `Pay_using_bank()`: Processes bill payments through the banking system.
  - `view_available_cars()`: Displays all cars available for rent.

---

## Installation and Setup

### **1. Prerequisites**
- A C++ compiler (e.g., GCC, Clang, or MSVC).
- Basic knowledge of C++.

### **2. Clone the Repository**
```bash
git clone https://github.com/admarspia/car-rental-system.git
cd car-rental-system
```

### **3. Compile the Code**
Use a C++ compiler to compile the source code. For example, with `g++`:
```bash
g++ -o car_rental main.cpp
```

### **4. Run the Program**
```bash
./car_rental
```

---

## Usage Guide

### **Main Menu**
1. **Customer Options**
   - Register as a new customer.
   - Rent a car and generate a bill.
   - Check your outstanding bill.

2. **Bank Options**
   - Register a new bank account.
   - Pay your car rental bill.

3. **Admin Options**
   - Add new cars.
   - Manage system data.

4. **Exit**

### **Payment Workflow**
1. Rent a car to generate a bill.
2. Go to the banking module to pay the bill.
3. Use your registered bank account to complete the transaction.

---

## Example Output

```plaintext
Welcome to the Car Rental System!

1. Register as a customer.
2. View available cars.
3. Rent a car.
4. Check outstanding bill.
5. Pay using bank account.
6. Exit.

Please select an option: 3
Enter your name: John Doe
Available Cars:
1. Toyota Corolla
2. Honda Civic
Select a car: 1
Bill generated: $100

Go to the banking module to pay your bill.
```

---

## Code Highlights

- **Encapsulation**: Classes and private attributes ensure data security.
- **Inheritance**: `Bank_Customer` inherits from `Customer` to enhance functionality.
- **Polymorphism**: Simplifies interactions between systems.

---

## Contributing

Contributions are welcome! If you'd like to contribute, please:
1. Fork the repository.
2. Create a feature branch: `git checkout -b feature-name`.
3. Commit your changes: `git commit -m 'Add feature-name'`.
4. Push to the branch: `git push origin feature-name`.
5. Open a pull request.

---

## Contact

For questions or feedback, please contact:
- **Name**: [Admarspis]
- **Email**: 1admarspias@gmail.com
- **GitHub**: [https://github.com/admarspia](https://github.com/admarspia)

---

Happy Coding!

