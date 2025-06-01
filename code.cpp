#include <iostream>
#include <ctime>  
#include <fstream>
#include <string>
#include <iomanip> 
using namespace std;
// ================= STRUCTURES =================
struct Credentials {
    string username;
    string password;
    string role;
};
struct DeliveryCompanyDetails {
    string username;
    string companyName;
    string companyType;
    float baseFare;
    string contactNumber;
    string serviceAreas;
};
struct CourierCompany {
    string name;
    string type; 
    float baseFare;
    bool isBlacklisted = false;
};

struct DeliveryRequest {
    string userUsername;
    string companyName;
    string parcelType;
    string status;
    string weight;
    string dimensions;
    string specialInstructions;
    string address;
    string orderDate; 
};
struct User {
    string username;
    string name;
    string address;
    string phone;
    string email;
};
// ================= GLOBAL ARRAYS =================
const int MAX_USERS = 10;
const int MAX_COMPANIES = 5;
const int MAX_DELIVERIES = 50;
const int MAX_USERS_DETAILS = 8;
const int MAX_COMPANY_DETAILS = 5;

DeliveryCompanyDetails companyDetails[MAX_COMPANY_DETAILS];
Credentials users[MAX_USERS];
CourierCompany companies[MAX_COMPANIES];
DeliveryRequest deliveries[MAX_DELIVERIES];
User userDetails[MAX_USERS_DETAILS];
int totalCompanyDetails = 0;
int totalUsers = 0;
int totalCompanies = 0;
int totalDeliveries = 0;
int totalUserDetails = 0;

// ================= FILE HANDLING =================
void loadUsers() {
    ifstream inFile("users.txt");
    totalUsers = 0;
    while (inFile >> users[totalUsers].username >> users[totalUsers].password >> users[totalUsers].role) {
        totalUsers++;
    }
    inFile.close();
}

void loadOrders() {
    ifstream inFile("orders.txt");
    if (!inFile) {
        cerr << "Error opening orders.txt" << endl;
        return;
    }
    DeliveryRequest order;
    while (getline(inFile, order.userUsername, '|') && 
           getline(inFile, order.companyName, '|') &&
           getline(inFile, order.parcelType, '|') &&
           getline(inFile, order.status, '|') &&
           getline(inFile, order.weight, '|') &&
           getline(inFile, order.dimensions, '|') &&
           getline(inFile, order.specialInstructions, '|') &&
           getline(inFile, order.address, '|') && 
           getline(inFile, order.orderDate)) { 
        deliveries[totalDeliveries++] = order; 
    }
    inFile.close();
}


void saveUsers() {
    ofstream outFile("users.txt");
    for (int i = 0; i < totalUsers; i++) {
        outFile << users[i].username << " " << users[i].password << " " << users[i].role << endl;
    }
    outFile.close();
}

void loadCompanies() {
       ifstream inFile("companies.txt");
       if (!inFile) {
           cerr << "Error opening companies.txt" << endl;
           return;
       }
       totalCompanies = 0;
       while (inFile >> companies[totalCompanies].name >> companies[totalCompanies].type >> companies[totalCompanies].baseFare >> companies[totalCompanies].isBlacklisted) {
           totalCompanies++;
       }
       inFile.close();
   }
void saveCompanies() {
    ofstream outFile("companies.txt");
    for (int i = 0; i < totalCompanies; i++) {
        outFile << companies[i].name << " " << companies[i].type << " " << companies[i].baseFare << " " << companies[i].isBlacklisted << endl;
    }
    outFile.close();
}
void loadCompanyDetails() {
    ifstream inFile("company_details.txt");
    if (!inFile) {
        cerr << "Error opening company_details.txt" << endl;
        return;
    }
    totalCompanyDetails = 0;
    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        DeliveryCompanyDetails temp;
        if (getline(iss, temp.username, '|') && 
            getline(iss, temp.companyName, '|') &&
            getline(iss, temp.companyType, '|') &&
            (iss >> temp.baseFare) && iss.ignore() &&
            getline(iss, temp.contactNumber, '|') &&
            getline(iss, temp.serviceAreas)) {
            
            companyDetails[totalCompanyDetails] = temp;
            
            // Add to companies array if not already present
            bool exists = false;
            for (int i = 0; i < totalCompanies; i++) {
                if (companies[i].name == temp.companyName) {
                    exists = true;
                    break;
                }
            }
            if (!exists && totalCompanies < MAX_COMPANIES) {
                companies[totalCompanies].name = temp.companyName;
                companies[totalCompanies].type = temp.companyType;
                companies[totalCompanies].baseFare = temp.baseFare;
                companies[totalCompanies].isBlacklisted = false;
                totalCompanies++;
            }
            totalCompanyDetails++;
        }
    }
    inFile.close();
    saveCompanies(); // Update companies.txt
}
   


void loadUserDetails() {
    ifstream inFile("userDetails.txt");
    if (!inFile) {
        cerr << "Error opening userDetails.txt" << endl;
        return;
    }
    
    totalUserDetails = 0;
    string line;
    while (getline(inFile, line) && totalUserDetails < MAX_USERS_DETAILS) {
        istringstream iss(line);
        User temp;
        if (getline(iss, temp.username, '|') && 
            getline(iss, temp.name, '|') &&
            getline(iss, temp.address, '|') &&
            getline(iss, temp.phone, '|') &&
            getline(iss, temp.email)) {
            
            userDetails[totalUserDetails] = temp;
            totalUserDetails++;
        }
    }
    inFile.close();
}

void saveUserDetails() { 
    ofstream outFile("userDetails.txt");
    for (int i = 0; i < totalUserDetails; i++) {
        outFile << userDetails[i].username << "|"
                << userDetails[i].name << "|"
                << userDetails[i].address << "|"
                << userDetails[i].phone << "|"
                << userDetails[i].email << endl;
    }
    outFile.close();
}


void saveCompanyDetails() {
    ofstream outFile("company_details.txt");
    for (int i = 0; i < totalCompanyDetails; i++) {
        outFile << companyDetails[i].username << "|"
                << companyDetails[i].companyName << "|"
                << companyDetails[i].companyType << "|"
                << companyDetails[i].baseFare << "|"
                << companyDetails[i].contactNumber << "|"
                << companyDetails[i].serviceAreas << endl;
    }
    outFile.close();
}

void loadDeliveryRequests() {
    ifstream inFile("deliveries.txt");
    totalDeliveries = 0;
    while (getline(inFile, deliveries[totalDeliveries].userUsername, '|') && 
           getline(inFile, deliveries[totalDeliveries].companyName, '|') &&
           getline(inFile, deliveries[totalDeliveries].parcelType, '|') &&
           getline(inFile, deliveries[totalDeliveries].status, '|') &&
           getline(inFile, deliveries[totalDeliveries].weight, '|') &&
           getline(inFile, deliveries[totalDeliveries].dimensions, '|') &&
           getline(inFile, deliveries[totalDeliveries].specialInstructions, '|') &&
           getline(inFile, deliveries[totalDeliveries].address, '|') &&
           getline(inFile, deliveries[totalDeliveries].orderDate)) {
        totalDeliveries++;
    }
    inFile.close();
}

void saveDeliveryRequests() {
    ofstream outFile("deliveries.txt");
    for (int i = 0; i < totalDeliveries; i++) {
        outFile << deliveries[i].userUsername << "|"
                << deliveries[i].companyName << "|"
                << deliveries[i].parcelType << "|"
                << deliveries[i].status << "|"
                << deliveries[i].weight << "|"
                << deliveries[i].dimensions << "|"
                << deliveries[i].specialInstructions << "|"
                << deliveries[i].address << "|"
                << deliveries[i].orderDate << endl;
    }
    outFile.close();
}
// ================= GENERAL =================
bool validateLogin(string username, string password, string &role) {
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].username == username && users[i].password == password) {
            role = users[i].role;
            return true;
        }
    }
    return false;
}


void registerUser() {
    if (totalUsers >= MAX_USERS) {
        cout << "User limit reached!" << endl;
        return;
    }

    Credentials newUser;
    User newDetails;
    string roleChoice;

    cout << "\n===== REGISTRATION =====\n";
    cout << "Select role:\n1. User\n2. Delivery Company\nEnter choice: ";
    cin >> roleChoice;

    if (roleChoice == "1") {
        newUser.role = "user";
    } else if (roleChoice == "2") {
        newUser.role = "delivery";
    } else {
        cout << "Invalid choice!" << endl;
        return;
    }

    cout << "Enter username: ";
    cin >> newUser.username;
    
    // Check if username already exists
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].username == newUser.username) {
            cout << "Username already exists! Please choose a different username." << endl;
            return;
        }
    }
    
    cout << "Enter password: ";
    cin >> newUser.password;

    if (newUser.role == "user") {
        // Collect user details for regular users
        if (totalUserDetails >= MAX_USERS_DETAILS) {
            cout << "Maximum user details reached!" << endl;
            return;
        }

        cout << "\n===== USER DETAILS =====\n";
        cout << "Enter your full name: ";
        cin.ignore();
        getline(cin, newDetails.name);
        
        cout << "Enter your address: ";
        getline(cin, newDetails.address);
        
        cout << "Enter your phone number: ";
        getline(cin, newDetails.phone);
        
        cout << "Enter your email: ";
        getline(cin, newDetails.email);

        // Store user details
        newDetails.username = newUser.username;
        userDetails[totalUserDetails] = newDetails;
        totalUserDetails++;
        saveUserDetails();
        
        cout << "User details saved successfully!" << endl;
    } 
    else if (newUser.role == "delivery") {
        if (totalCompanyDetails >= MAX_COMPANY_DETAILS) {
            cout << "Maximum delivery companies reached!" << endl;
            return;
        }

        DeliveryCompanyDetails newCompany;
        newCompany.username = newUser.username;

        cout << "\n===== COMPANY REGISTRATION =====" << endl;
        cout << "Enter company name: ";
        cin.ignore();
        getline(cin, newCompany.companyName);
        
        cout << "Enter company type (Express/Standard/Heavy): ";
        getline(cin, newCompany.companyType);
        
        cout << "Enter base fare: $";
        cin >> newCompany.baseFare;
        
        cout << "Enter contact number: ";
        cin.ignore();
        getline(cin, newCompany.contactNumber);
        
        cout << "Enter service areas (comma separated): ";
        getline(cin, newCompany.serviceAreas);

        companyDetails[totalCompanyDetails] = newCompany;
        totalCompanyDetails++;
        saveCompanyDetails();

        if (totalCompanies < MAX_COMPANIES) {
            companies[totalCompanies].name = newCompany.companyName;
            companies[totalCompanies].type = newCompany.companyType;
            companies[totalCompanies].baseFare = newCompany.baseFare;
            companies[totalCompanies].isBlacklisted = false;
            totalCompanies++;
            saveCompanies();
        }
    }

    users[totalUsers++] = newUser;
    saveUsers();
    cout << "Registration successful as " << newUser.role << "!" << endl;
}

// ================= USER FUNCTIONS =================


// ============================= CALENDAR =============================
int getFirstWeekday(int month) {
    int y = 2025;
    int m = month;
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int q = 1; 
    int k = y % 100;
    int j = y / 100;
    int h = (q + 13*(m+1)/5 + k + k/4 + j/4 + 5*j) % 7;
   
    int d = ((h + 6) % 7); 
    return d;
}
int getDaysInMonth(int month) {
    switch(month) {
        case 1: return 31;
        case 2: return 28; 
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 30;
    }
}
string getMonthName(int month) {
    const string months[12] = {"January", "February", "March", "April", "May", "June",
                               "July", "August", "September", "October", "November", "December"};
    if (month < 1 || month > 12) return "";
    return months[month-1];
}

void printCalendar(int month) {
    cout << "\n=== " << getMonthName(month) << " 2025 ===" << endl;
    cout << "Su Mo Tu We Th Fr Sa" << endl;
    int firstDay = getFirstWeekday(month);
    int daysInMonth = getDaysInMonth(month);
    int currentDay = 1;
    for (int i = 0; i < firstDay; ++i) {
        cout << "   ";
    }
 
    for (int i = firstDay; i < 7; ++i) {
        cout << setw(2) << currentDay << " ";
        currentDay++;
    }
    cout << endl;
    while (currentDay <= daysInMonth) {
        for (int i = 0; i < 7 && currentDay <= daysInMonth; ++i) {
            cout << setw(2) << currentDay << " ";
            currentDay++;
        }
        cout << endl;
    }
}
// ============================= CALENDAR =============================




void requestDelivery(string username) {
    if (totalDeliveries >= MAX_DELIVERIES) {
        cout << "Maximum delivery requests reached!" << endl;
        return;
    }
    
    // Reload companies to ensure we have the latest data
    loadCompanyDetails();
    DeliveryRequest newDelivery;
    newDelivery.userUsername = username;
    
    cout << "\n===== PARCEL DETAILS FORM =====" << endl;
    cout << "Enter parcel type (Document/Box/Fragile/etc.): ";
    cin.ignore();
    getline(cin, newDelivery.parcelType);
    cout << "Enter approximate weight (kg): ";
    getline(cin, newDelivery.weight);
    cout << "Enter dimensions (LxWxH in cm): ";
    getline(cin, newDelivery.dimensions);
    cout << "Enter delivery address: ";
    getline(cin, newDelivery.address);  // This is the delivery address the user wants
    cout << "Any special instructions: ";
    getline(cin, newDelivery.specialInstructions);


    time_t now = time(0);
    tm *ltm = localtime(&now);

    int displayMonth = (ltm->tm_mday > 15) ? (ltm->tm_mon + 2) : (ltm->tm_mon + 1); 
    if (displayMonth > 12) displayMonth = 1; 

    printCalendar(displayMonth);

    int selectedDate;
    int maxDays = getDaysInMonth(displayMonth);

    do {
        cout << "Select a delivery date (1-" << maxDays << "): ";
        cin >> selectedDate;
        if (selectedDate < 1 || selectedDate > maxDays) {
            cout << "Invalid date! Please choose a valid date within the displayed calendar.\n";
        }
    } while (selectedDate < 1 || selectedDate > maxDays);

    char dateBuffer[11];
    sprintf(dateBuffer, "2025-%02d-%02d", displayMonth, selectedDate);
    newDelivery.orderDate = dateBuffer;
    // DO NOT overwrite the delivery address here - keep the user's input

    cout << "\n===== AVAILABLE DELIVERY COMPANIES =====" << endl;
    if (totalCompanyDetails == 0) {
        cout << "No delivery companies available!" << endl;
        return;
    }

    int availableCompanies = 0;
    for (int i = 0; i < totalCompanyDetails; i++) {
        bool isBlacklisted = false;
        for (int j = 0; j < totalCompanies; j++) {
            if (companies[j].name == companyDetails[i].companyName && companies[j].isBlacklisted) {
                isBlacklisted = true;
                break;
            }
        }
        if (!isBlacklisted) {
            availableCompanies++;
            cout << availableCompanies << ") " << companyDetails[i].companyName;
            cout << " - Base Fare: $" << companyDetails[i].baseFare;
            cout << "\n   Type: " << companyDetails[i].companyType;
            cout << "\n   Contact: " << companyDetails[i].contactNumber;
            cout << "\n   Service Areas: " << companyDetails[i].serviceAreas;
            cout << "\n-----------------------------------" << endl;
        }
    }
    
    if (availableCompanies == 0) {
        cout << "No available delivery companies!" << endl;
        return;
    }

    int choice;
    do {
        cout << "\nSelect a company (1-" << availableCompanies << "): ";
        cin >> choice;
        if (choice < 1 || choice > availableCompanies) {
            cout << "Invalid selection! Please choose a valid company number." << endl;
        }
    } while (choice < 1 || choice > availableCompanies);

    int selectedIndex = 0;
    int count = 0;
    for (int i = 0; i < totalCompanyDetails; i++) {
        bool isBlacklisted = false;
        for (int j = 0; j < totalCompanies; j++) {
            if (companies[j].name == companyDetails[i].companyName) {
                isBlacklisted = companies[j].isBlacklisted;
                break;
            }
        }
        if (!isBlacklisted) {
            count++;
            if (count == choice) {
                selectedIndex = i;
                break;
            }
        }
    }
    
    newDelivery.companyName = companyDetails[selectedIndex].companyName;
    newDelivery.status = "Pending";
    deliveries[totalDeliveries] = newDelivery;
    totalDeliveries++;

    // Save the delivery request immediately after adding it
    saveDeliveryRequests();

    // Append to orders.txt
    ofstream ordersFile("orders.txt", ios::app);
    if (ordersFile.is_open()) {
        ordersFile << newDelivery.userUsername << "|"
                   << newDelivery.companyName << "|"
                   << newDelivery.parcelType << "|"
                   << newDelivery.status << "|"
                   << newDelivery.weight << "|"
                   << newDelivery.dimensions << "|"
                   << newDelivery.specialInstructions << "|"
                   << newDelivery.address << "|"
                   << newDelivery.orderDate << endl; 
        ordersFile.close();
    } else {
        cerr << "Error opening orders.txt for writing!" << endl;
    }

    cout << "\n===== ORDER CONFIRMATION =====" << endl;
    cout << "Company: " << newDelivery.companyName << endl;
    cout << "Parcel Type: " << newDelivery.parcelType << endl;
    cout << "Weight: " << newDelivery.weight << " kg" << endl;
    cout << "Dimensions: " << newDelivery.dimensions << endl;
    cout << "Delivery Address: " << newDelivery.address << endl;
    cout << "Special Instructions: " << newDelivery.specialInstructions << endl;
    cout << "Status: " << newDelivery.status << endl;
    cout << "Delivery Date: " << newDelivery.orderDate << endl;
    cout << "Estimated Cost: $" << (companyDetails[selectedIndex].baseFare + (companyDetails[selectedIndex].baseFare * 0.5)) << endl;
    cout << "Thank you for your order!" << endl;
}


void userMenu(string username) {
    int choice;
    while (true) {
        cout << "\n===== USER MENU =====\n1. Request Delivery\n2. View My Orders\n3. Logout\nEnter choice: ";
        cin >> choice;
        if (choice == 1)
            requestDelivery(username);
        else if (choice == 2) {
            cout << "\n===== YOUR ORDERS =====\n";
            bool found = false;
            for (int i = 0; i < totalDeliveries; i++) {
                if (deliveries[i].userUsername == username) {
                    cout << "Order #" << i+1 << endl;
                    cout << "Company: " << deliveries[i].companyName << endl;
                    cout << "Order Date: " << deliveries[i].orderDate << endl;
                    cout << "Parcel Type: " << deliveries[i].parcelType << endl;
                    cout << "Weight: " << deliveries[i].weight << " kg" << endl;
                    cout << "Dimensions: " << deliveries[i].dimensions << endl;
                    cout << "Delivery Address: " << deliveries[i].address << endl;
                    cout << "Special Instructions: " << deliveries[i].specialInstructions << endl;
                    cout << "Current Status: " << deliveries[i].status << endl;
                    cout << "---------------------------" << endl;
                    found = true;
                }
            }
            if (!found) cout << "No orders found!" << endl;
        }
        else if (choice == 3)
            break;
        else
            cout << "Invalid choice!" << endl;
    }
}

// ================= DELIVERY FUNCTIONS =================
void deliveryMenu(string username) {
    string companyName;
    for (int i = 0; i < totalCompanyDetails; i++) {
        if (companyDetails[i].username == username) {
            companyName = companyDetails[i].companyName;
            break;
        }
    }

    int choice;
    while (true) {
        cout << "\n===== DELIVERY MENU =====\n1. View Current Orders\n2. Update Order Status\n3. Logout\nEnter choice: ";
        cin >> choice;
        
    if (choice == 1) {
        cout << "\n===== CURRENT ORDERS =====\n";
        bool found = false;
        for (int i = 0; i < totalDeliveries; i++) {
                if (deliveries[i].companyName == companyName) { 
                cout << "Order #" << i+1 << endl;
                cout << "User: " << deliveries[i].userUsername << endl;
                cout << "Order Date: " << deliveries[i].orderDate << endl;
                cout << "Delivery Address: " << deliveries[i].address << endl;
                cout << "Parcel Type: " << deliveries[i].parcelType << endl;
                cout << "Weight: " << deliveries[i].weight << " kg" << endl;
                cout << "Dimensions: " << deliveries[i].dimensions << endl;
                cout << "Special Instructions: " << deliveries[i].specialInstructions << endl;
                cout << "Current Status: " << deliveries[i].status << endl;
                cout << "---------------------------" << endl;
                found = true;
        }
    }
        if (!found) cout << "No orders found!" << endl;
    }

        else if (choice == 2) {
            cout << "\n===== UPDATE ORDER STATUS =====" << endl;
            bool hasOrders = false;
            for (int i = 0; i < totalDeliveries; i++) {
                if (deliveries[i].companyName == companyName) {
                    cout << i+1 << ". Order from " << deliveries[i].userUsername 
                         << " (" << deliveries[i].status << ")" << endl;
                    hasOrders = true;
                }
            }
            
            if (!hasOrders) {
                cout << "No orders to update!" << endl;
                continue;
            }

            cout << "\nEnter order number to update: ";
            int orderNum;
            cin >> orderNum;
            orderNum--; 

            if (orderNum < 0 || orderNum >= totalDeliveries) {
                cout << "Invalid order number!" << endl;
                continue;
            }

            if (deliveries[orderNum].companyName != companyName) {
                cout << "This order doesn't belong to your company!" << endl;
                continue;
            }

            cout << "\nCurrent status: " << deliveries[orderNum].status << endl;
            cout << "Select new status:\n";
            cout << "1. Pending\n2. In Transit\n3. Delivered\n4. Cancelled\n";
            cout << "Enter choice (1-4): ";
            int statusChoice;
            cin >> statusChoice;

            switch(statusChoice) {
                case 1: deliveries[orderNum].status = "Pending"; break;
                case 2: deliveries[orderNum].status = "In Transit"; break;
                case 3: deliveries[orderNum].status = "Delivered"; break;
                case 4: deliveries[orderNum].status = "Cancelled"; break;
                default:
                    cout << "Invalid choice! Status not updated." << endl;
                    continue;
            }

            saveDeliveryRequests();
            cout << "Status updated to: " << deliveries[orderNum].status << endl;
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
}

// ================= ADMIN FUNCTIONS =================
void viewAllCompanies() {
    cout << "\n===== REGISTERED COMPANIES =====" << endl;
    if (totalCompanyDetails == 0) {
        cout << "No registered delivery companies found." << endl;
        return;
    }
    for (int i = 0; i < totalCompanyDetails; i++) {
        cout << "#" << (i + 1) << " " << companyDetails[i].companyName;
        bool blacklisted = false;
        for (int j = 0; j < totalCompanies; j++) {
            if (companies[j].name == companyDetails[i].companyName) {
                blacklisted = companies[j].isBlacklisted;
                break;
            }
        }
        if (blacklisted) {
            cout << " - Blacklisted";
        }
        cout << endl;
    }
}

void generateUserReport() {
    cout << "\n===== USER REPORT =====\n";
    
    // Count and display all users with "user" role
    int userCount = 0;
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].role == "user") {
            userCount++;
            cout << "#" << userCount << " " << users[i].username << endl;
        }
    }
    
    if (userCount == 0) {
        cout << "No users found!" << endl;
    } else {
        cout << "\nTotal users: " << userCount << endl;
    }
}


void generateDeliveryReport() {
    cout << "\n===== DELIVERY REPORT =====\n";
    for (int i = 0; i < totalDeliveries; i++) {
        cout << "#" << (i + 1) << " Delivery Request" << endl;
        cout << "User: " << deliveries[i].userUsername << endl;
        cout << "Company: " << deliveries[i].companyName << endl;
        cout << "Parcel: " << deliveries[i].parcelType << endl;
        cout << "Status: " << deliveries[i].status << endl;
        cout << "Weight: " << deliveries[i].weight << " kg" << endl;
        cout << "Dimensions: " << deliveries[i].dimensions << endl;
        cout << "Delivery Address: " << deliveries[i].address << endl;
        cout << "Special Instructions: " << deliveries[i].specialInstructions << endl;
        cout << "Order Date: " << deliveries[i].orderDate << endl;
        cout << "---------------------------" << endl;
    }
}

void blacklistCompany() {
    if (totalCompanies == 0) {
        cout << "No companies to blacklist." << endl;
        return;
    }
    cout << "\n===== BLACKLIST COMPANIES =====" << endl;
    for (int i = 0; i < totalCompanies; i++) {
        cout << (i + 1) << ") " << companies[i].name;
        if (companies[i].isBlacklisted) cout << " - Already Blacklisted";
        cout << endl;
    }
    cout << "Enter the number of the company to blacklist (0 to cancel): ";
    int choice;
    cin >> choice;
    if (choice == 0) {
        cout << "Blacklist operation cancelled." << endl;
        return;
    }
    if (choice < 1 || choice > totalCompanies) {
        cout << "Invalid choice!" << endl;
        return;
    }
    int idx = choice - 1;
    if (companies[idx].isBlacklisted) {
        cout << companies[idx].name << " is already blacklisted." << endl;
        return;
    }
    companies[idx].isBlacklisted = true;
    saveCompanies();
    cout << companies[idx].name << " is now blacklisted." << endl;
}

void removeCompany() {
    viewAllCompanies();
    cout << "\nEnter company name to remove: ";
    string name;
    cin.ignore();
    getline(cin, name);
    
    // Remove from companies array
    for (int i = 0; i < totalCompanies; i++) {
        if (companies[i].name == name) {
            for (int j = i; j < totalCompanies - 1; j++) {
                companies[j] = companies[j + 1];
            }
            totalCompanies--;
            break;
        }
    }
    
    // Remove from companyDetails array
    for (int i = 0; i < totalCompanyDetails; i++) {
        if (companyDetails[i].companyName == name) {
            for (int j = i; j < totalCompanyDetails - 1; j++) {
                companyDetails[j] = companyDetails[j + 1];
            }
            totalCompanyDetails--;
            break;
        }
    }
    
    // Remove associated deliveries
    for (int i = 0; i < totalDeliveries; i++) {
        if (deliveries[i].companyName == name) {
            for (int j = i; j < totalDeliveries - 1; j++) {
                deliveries[j] = deliveries[j + 1];
            }
            totalDeliveries--;
            i--; // Check current index again as elements shifted
        }
    }
    
    saveCompanies();
    saveCompanyDetails();
    saveDeliveryRequests();
    cout << "Company and all associated data removed successfully." << endl;
}


void managementToolsMenu() {
    int choice;
    while (true) {
        cout << "\n===== MANAGEMENT TOOLS =====\n1. Blacklist Company\n2. Remove Company\n3. Back\nEnter choice: ";
        cin >> choice;
        if (choice == 1)
            blacklistCompany();
        else if (choice == 2)
            removeCompany();
        else if (choice == 3)
            break;
        else
            cout << "Invalid option." << endl;
    }
}

void adminMenu() {
    int choice;
    while (true) {
        cout << "\n===== ADMIN MENU =====\n1. User Reports\n2. Delivery Reports\n3. View All Companies\n4. Management Tools\n5. Logout\nEnter choice: ";
        cin >> choice;
        if (choice == 1)
            generateUserReport();
        else if (choice == 2)
            generateDeliveryReport(); 
        else if (choice == 3)
            viewAllCompanies();
        else if (choice == 4)
            managementToolsMenu();
        else if (choice == 5)
            break;
        else
            cout << "Invalid choice!" << endl;
    }
}

// ================= MAIN =================
int main() {
    loadUsers();
    loadCompanies();
    loadUserDetails();
    loadCompanyDetails();
    loadDeliveryRequests();
    loadOrders();

     bool adminExists = false;
    for (int i = 0; i < totalUsers; i++) {
        if (users[i].role == "admin") {
            adminExists = true;
            break;
        }
    }
    if (!adminExists) {
        users[totalUsers].username = "admin";
        users[totalUsers].password = "123";
        users[totalUsers].role = "admin";
        totalUsers++;
        saveUsers();
    }
   while (true) {
        cout << "\n===== COURIER MANAGEMENT SYSTEM =====\n1. Login\n2. Register\n3. Exit\nEnter choice: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            string username, password, role;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (validateLogin(username, password, role)) {
                cout << "Login successful as " << role << "!" << endl;
                if (role == "admin") adminMenu();
                else if (role == "user") userMenu(username);
                else if (role == "delivery") deliveryMenu(username);
                else cout << "Unknown role!" << endl;
            } else {
                cout << "Invalid credentials!" << endl;
            }
        } else if (choice == 2) {
            registerUser();
        } else if (choice == 3) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid option!" << endl;
        }
    }
    return 0;
}

