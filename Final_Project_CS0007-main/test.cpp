#include <iostream>
#include "part1_2.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

struct Customer {
    std::string name;
    int bookingHistory;
    int preferredRoom;
    int bookingDate;
};

std::vector<Customer> customers;
std::vector<Customer> priorityList;

void insertionSort(std::vector<Customer>& customers) {
    int n = customers.size();
    for (int i = 1; i < n; ++i) {
        Customer key = customers[i];
        int j = i - 1;
        while (j >= 0 && customers[j].bookingHistory > key.bookingHistory) {
            customers[j + 1] = customers[j];
            --j;
        }
        customers[j + 1] = key;
    }
}

bool sortByPreferredRoom(const Customer& a, const Customer& b) {
    return a.preferredRoom < b.preferredRoom; 
}

void readCustomerData(std::vector<Customer>& customers) {
    customers.clear();
    std::ifstream inFile("customer_data.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open file for reading.\n";
        return; 
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        Customer customer;
        std::istringstream iss(line);
        std::getline(iss, customer.name, ',');
        iss >> customer.bookingHistory;
        iss.ignore();
        iss >> customer.bookingDate;
        iss.ignore();
        iss >> customer.preferredRoom;
        customers.push_back(customer);
    }

    inFile.close();
}

void displayBookingLogs() {
    readCustomerData(customers);

    std::cout << "===== Booking Logs =====\n";
    if (customers.empty()) {
        std::cout << "No booking records found.\n";
        return;
    }

    for (const auto& customer : customers) {
    
        if (customer.bookingDate < 1 || customer.bookingDate > 12) {
            std::cout << "Invalid booking date for customer: " << customer.name << ". Skipping...\n";
            continue;
        }
        
        if (customer.preferredRoom < 1 || customer.preferredRoom > 5) {
            std::cout << "Invalid preferred room for customer: " << customer.name << ". Skipping...\n";
            continue;
        }

        std::vector<std::string> monthNames = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        std::vector<std::string> roomNames = {"Standard Queen", "Standard King", "Standard King - Connecting", "Deluxe", "Suite"};

        std::cout << "\nName: " << customer.name << "\n";
        std::cout << "Booking History: " << customer.bookingHistory << "\n";
        std::cout << "Preferred Room: " << roomNames[customer.preferredRoom - 1] << "\n";
        std::cout << "Booking Date: " << monthNames[customer.bookingDate - 1] << "\n\n";
    }
}

void displayPriorityList() {
    readCustomerData(customers);
    priorityList = customers;
    insertionSort(priorityList);

    std::cout << "===== Priority List (Sorted by Number of Bookings) =====\n";
    if (priorityList.empty()) {
        std::cout << "No booking records found.\n";
        return;
    }

    for (int i = priorityList.size() - 1; i >= 0; --i) {
        const auto& customer = priorityList[i];
        std::cout << "Name: " << customer.name << "\n";
        std::cout << "Booking History: " << customer.bookingHistory << "\n";
    }
}

double calculateDiscountedPrice(const Customer& customer, int basePrice) {
    double discountedPrice = basePrice;

    if (customer.bookingHistory >= 10) {
        
        discountedPrice *= 0.95;
    } else if (customer.bookingHistory >= 5) {
        
        discountedPrice *= 0.97;

    }

    return discountedPrice;
}


void CustomerInfo() {
    PartOne_Two function;
    // Read market data from files
    function.readData("marketData_1Jan.csv");
    function.readData("marketData_2Feb.csv");
    function.readData("marketData_3Mar.csv");
    function.readData("marketData_4Apr.csv");
    function.readData("marketData_5May.csv");
    function.readData("marketData_6Jun.csv");
    function.readData("marketData_7Jul.csv");
    function.readData("marketData_8Aug.csv");
    function.readData("marketData_9Sep.csv");
    function.readData("marketData_10Oct.csv");
    function.readData("marketData_11Nov.csv");
    function.readData("marketData_12Dec.csv");
    
    Customer customer;
    std::cout << "Enter customer name: ";
    std::cin >> customer.name;
    std::cout << "Enter booking history: ";
    std::cin >> customer.bookingHistory;
    do {
        std::cout << "Enter booking Month(1-12, Price may vary): ";
        std::cin >> customer.bookingDate;
        if (customer.bookingDate < 1 || customer.bookingDate > 12) {
            std::cout << "Invalid month. Please enter a value between 1 and 12.\n";
        }
    } while (customer.bookingDate < 1 || customer.bookingDate > 12);
    do {
        std::cout << "[1]-Standard Queen [2]-Standard King\n";
        std::cout << "[3]-Standard King - Connecting [4]-Deluxe\n";
        std::cout << "[5]-Suite\n";
        std::cout << "Enter preferred room: ";
        std::cin >> customer.preferredRoom;
        if (customer.preferredRoom < 1 || customer.preferredRoom > 5) {
            std::cout << "Invalid room choice. Please enter a value between 1 and 5.\n";
        }
    } while (customer.preferredRoom < 1 || customer.preferredRoom > 5);

    
    std::ofstream outFile("customer_data.txt", std::ios::app); 
    if (outFile.is_open()) {
        outFile << customer.name << "," << customer.bookingHistory << "," << customer.bookingDate << "," << customer.preferredRoom << std::endl;
        
        outFile.close();
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
    int basePrice = function.dynamicPricing(customer.preferredRoom-1, customer.bookingDate-1);

    std::cout << "The base price for " << basePrice;
    

    if(customer.bookingHistory==0){
        std::cout<<"\nYour total price is: "<< basePrice;
    }else{
        int discounted = calculateDiscountedPrice(customer, basePrice);
        std::cout<<"\nYour discounted price is: "<<discounted<<std::endl;
    }


}  

void displayMenu() {
    std::cout << "\n\n===== MENU =====\n";
    std::cout << "1. Add Booking\n";
    std::cout << "2. Booking Logs\n";
    std::cout << "3. Priority List\n";
    std::cout << "4. Exit\n";
}

int main() {
    PartOne_Two function;
    char choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case '1':
                CustomerInfo();
                break;
            case '2':
                displayBookingLogs();
                break;
            case '3':
                displayPriorityList(); // Display sorted booking logs
                break;
            case '4':
                std::cout << "Exiting Program\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '4');

    return 0;
}