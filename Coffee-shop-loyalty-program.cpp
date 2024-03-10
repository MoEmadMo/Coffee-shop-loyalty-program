#include <iostream>
#include <string>
#include "algorithm"
using namespace std;

const int MAXN = 100;
int VisID[MAXN];
int VisCustomer[MAXN];

double customerID[MAXN], customerWallet[MAXN], customerPoints[MAXN];
string customerPhoneNumber[MAXN];

double itemID[MAXN], itemPrice[MAXN];
string itemName[MAXN];

int nCustomers = 3, nItems = 5;

int itemIndexByName[MAXN];

void displayMenu() {
    cout << "1. Add customer" << endl;
    cout << "2. Add a menu item" << endl;
    cout << "3. Print all customers" << endl;
    cout << "4. Print all items" << endl;
    cout << "5. Make order" << endl;
    cout << "6. Redeem Item" << endl;
    cout << "7. Show the customer with the highest points" << endl;
    cout << "8. Show customer data" << endl;
    cout << "9. Display menu" << endl;
    cout << "10. Sort based on points earned" << endl;
    cout << "11. Exit " << endl;
}

bool checkCustomer(int id) {
    return (!VisCustomer[id]);
}

bool CustomSort(int l , int r) {
    return customerPoints[l] > customerPoints[r];
}

void SortByPoints() {
    int temp[MAXN] = {};
    for (int i = 0 ; i < MAXN ; i++){
        temp[i] = i;
    }
    sort(temp , temp+MAXN , CustomSort);
    for (int i : temp){
        if (customerPoints[i] != 0) {
            cout << "The id " << i + 1 << " has points : " <<
                 customerPoints[i] << '\n';
        }
    }
    cout << '\n';
}

void addCustomer() {
    int id, wallet;
    string phoneNumber;
    while (true) {
        cout << "Enter customer ID: \n";
        cin >> id;
        if (!checkCustomer(id)) {
            cout << "The ID is already used \n";
        } else {
            break;
        }
    }
    cout << "Enter phone number: \n";
    cin >> phoneNumber;
    cout << "Enter wallet amount: \n";
    cin >> wallet;
    customerID[nCustomers] = id;
    customerPhoneNumber[nCustomers] = phoneNumber;
    customerWallet[nCustomers] = wallet;
    customerPoints[nCustomers] = 0;
    VisCustomer[id] = 1;
    nCustomers++;
    cout << "Customer added successfully." << endl;
}

bool check(int ID, const string& Name) {
    for (int i = 0; i < nItems; i++) {
        if (VisID[ID] || (itemIndexByName[i] != -1 && itemName[i] == Name)) {
            return false;
        }
    }
    return true;
}

void addItem() {
    int id, price;
    string name;
    while (true) {
        cout << "Enter item ID: \n";
        cin >> id;
        cout << "Enter item name: \n";
        cin >> name;
        if (!check(id, name)) {
            cout << "The ID or name is already used \n";
        } else {
            break;
        }
    }
    cout << "Enter item price: \n";
    cin >> price;
    itemID[nItems] = id;
    itemName[nItems] = name;
    itemPrice[nItems] = price;
    VisID[id] = 1;
    itemIndexByName[nItems] = id;
    nItems++;
    cout << "Item added successfully." << endl;
}

void printCustomers() {
    cout << "Customer ID\tPhone Number\tWallet\tPoints" << endl;
    for (int i = 0; i < nCustomers; i++) {
        cout << customerID[i] << "\t\t" << customerPhoneNumber[i] << "\t" << customerWallet[i] << "\t" << customerPoints[i] << endl;
    }
}

void printItems() {
    cout << "Item ID\t\tName\t\tPrice" << endl;
    for (int i = 0; i < nItems; i++) {
        cout << itemID[i] << "\t\t" << itemName[i] << "\t\t" << itemPrice[i] << endl;
    }
}



void makeOrder() {
    int customerId, itemId , x_items;
    while (true) {
        cout << "Enter customer ID: \n";
        cin >> customerId;
        cout << "Enter item ID: \n";
        cin >> itemId;
        cout << "Enter the number of items you want to order\n";
        cin >> x_items;
        int customerIndex = -1, itemIndex = -1;
        for (int i = 0; nCustomers; i++) {
            if (customerID[i] == customerId) {
                customerIndex = i;
                break;
            }
        }
        for (int i = 0; nItems; i++) {
            if (itemID[i] == itemId) {
                itemIndex = i;
                break;
            }
        }
        if (customerIndex != -1 && itemIndex != -1) {
            if (customerWallet[customerIndex] >= itemPrice[itemIndex]) {
                customerWallet[customerIndex] -= x_items*itemPrice[itemIndex];
                double earnedPoints = itemPrice[itemIndex] / 4.0;
                customerPoints[customerIndex] += x_items*earnedPoints;
                cout << "Order placed successfully." << endl;
            } else {
                cout << "Insufficient wallet balance." << endl;
            }
            break;
        } else {
            cout << "Invalid item ID or customer ID \n";
        }
    }
}

void redeemItem() {
    int customerId, itemId;
    cout << "Enter customer ID: ";
    cin >> customerId;
    cout << "Enter item ID: ";
    cin >> itemId;
    int customerIndex = -1, itemIndex = -1;
    for (int i = 0; i < nCustomers; i++) {
        if (customerID[i] == customerId) {
            customerIndex = i;
            break;
        }
    }
    for (int i = 0; i < nItems; i++) {
        if (itemID[i] == itemId) {
            itemIndex = i;
            break;
        }
    }
    if (customerIndex != -1 && itemIndex != -1) {
        if (customerPoints[customerIndex] >= itemPrice[itemIndex] * 4) {
            customerPoints[customerIndex] -= itemPrice[itemIndex] * 4;
            cout << "Item redeemed successfully." << endl;
        } else {
            cout << "Insufficient points to redeem the item." << endl;
        }
    }
    else {
        cout << "Invalid customer ID or item ID." << endl;
    }
}

void showCustomerData() {
    int customerId;
    cout << "Enter customer ID: ";
    cin >> customerId;
    int customerIndex = -1;
    for (int i = 0; i < nCustomers; i++) {
        if (customerID[i] == customerId) {
            customerIndex = i;
            break;
        }
    }
    if (customerIndex != -1) {
        cout << "Phone Number: " << customerPhoneNumber[customerIndex] << endl;
        cout << "Wallet: " << customerWallet[customerIndex] << endl;
        cout << "Points: " << customerPoints[customerIndex] << endl;
    } else {
        cout << "Invalid customer ID." << endl;
    }
}

void showCustomerWithHighestPoints() {
    int maxPoints = 0;
    for (int i = 0; i < nCustomers; i++) {
        maxPoints = max(maxPoints, int(customerPoints[i]));
    }
    int customerIndex = -1;
    for (int i = 0; i < nCustomers; i++) {
        if (customerPoints[i] == maxPoints) {
            customerIndex = i;
            break;
        }
    }
    cout << "Customer with the highest points: " << endl;
    cout << "Customer ID: " << customerID[customerIndex] << endl;
    cout << "Phone Number: " << customerPhoneNumber[customerIndex] << endl;
    cout << "Wallet: " << customerWallet[customerIndex] << endl;
    cout << "Points: " << customerPoints[customerIndex] << endl;
}

int main() {
    customerID[0] = 1, customerID[1] = 2, customerID[2] = 3;
    customerPhoneNumber[0] = "0123456789", customerPhoneNumber[1] = "0123456788", customerPhoneNumber[2] = "0123456787";
    customerWallet[0] = 1000, customerWallet[1] = 2000, customerWallet[2] = 5000;
    customerPoints[0] = 0, customerPoints[1] = 0, customerPoints[2] = 0;
    VisCustomer[1] = 1, VisCustomer[2] = 1, VisCustomer[3] = 1;
    itemID[0] = 1, itemID[1] = 2, itemID[2] = 3, itemID[3] = 4, itemID[4] = 5;
    itemName[0] = "cappuccino", itemName[1] = "espresso", itemName[2] = "Turkish coffee", itemName[3] = "lemon", itemName[4] = "orange";
    itemPrice[0] = 30, itemPrice[1] = 50, itemPrice[2] = 50, itemPrice[3] = 25, itemPrice[4] = 25;
    VisID[1] = 1, VisID[2] = 1, VisID[3] = 1, VisID[4] = 1, VisID[5] = 1;
    for (int i = 0; i < nItems; i++) {
        itemIndexByName[i] = -1;
    }

    while (true) {
        displayMenu();
        int ch;
        cin >> ch;
        if (ch == 1)
            addCustomer();
        else if (ch == 2)
            addItem();
        else if (ch == 3)
            printCustomers();
        else if (ch == 4)
            printItems();
        else if (ch == 5)
            makeOrder();
        else if (ch == 6)
            redeemItem();
        else if (ch == 7)
            showCustomerWithHighestPoints();
        else if (ch == 8)
            showCustomerData();
        else if (ch == 9)
            displayMenu();
        else if (ch == 10){
            SortByPoints();
        }
        else if (ch == 11)
            break;

        else {
            cout << "Invalid choice :( \n";
        }
    }
    return 0;
}