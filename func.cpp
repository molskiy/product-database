#include "func.h"
#include <fstream>
using namespace std;

namespace Shop {
    Product::Product() : name(""), price(0.0), quantity(0) {}
    
    Product::Product(string n, double p, int q) 
        : name(n), price(p), quantity(q) {}
    
    string Product::getName() const { return name; }
    double Product::getPrice() const { return price; }
    int Product::getQuantity() const { return quantity; }
    
    void Product::setName(string n) { name = n; }
    void Product::setPrice(double p) { price = p; }
    void Product::setQuantity(int q) { quantity = q; }
    
    void Product::display() const {
        cout << *this;
    }
    
    ostream& operator<<(ostream& os, const Product& p) {
        os << "Name: " << p.name << ", Price: " << p.price 
           << ", Quantity: " << p.quantity;
        return os;
    }
    
    istream& operator>>(istream& is, Product& p) {
        is >> p.name >> p.price >> p.quantity;
        return is;
    }

    Database::Database(const string& fname) 
        : products(nullptr), size(0), capacity(0), filename(fname) {
        loadFromFile();
    }
    
    Database::~Database() {
        saveToFile();
        delete[] products;
    }
    
    void Database::resize() {
        capacity = capacity == 0 ? 1 : capacity * 2;
        Product* newArray = new Product[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = products[i];
        }
        delete[] products;
        products = newArray;
    }
    
    void Database::loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            Product p;
            while (file >> p) {
                if (size == capacity) resize();
                products[size++] = p;
            }
            file.close();
        }
    }
    
    void Database::saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < size; i++) {
                file << products[i] << "\n";
            }
            file.close();
        }
    }
    
    void Database::displayAll() const {
        cout << *this;
    }
    
    void Database::addProduct(const Product& p) {
        if (size == capacity) resize();
        products[size++] = p;
    }
    
    void Database::removeProduct(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; i++) {
                products[i] = products[i + 1];
            }
            size--;
        }
    }
    
    void Database::editProduct(int index) {
        if (index >= 0 && index < size) {
            cout << "Enter new product data (name price quantity): ";
            cin >> products[index];
        }
    }
    
    void Database::searchByName(const string& name) const {
        for (int i = 0; i < size; i++) {
            if (products[i].getName().find(name) != string::npos) {
                cout << products[i] << endl;
            }
        }
    }
    
    void Database::searchByPrice(double maxPrice) const {
        for (int i = 0; i < size; i++) {
            if (products[i].getPrice() <= maxPrice) {
                cout << products[i] << endl;
            }
        }
    }
    
    ostream& operator<<(ostream& os, const Database& db) {
        for (int i = 0; i < db.size; i++) {
            os << i + 1 << ". " << db.products[i] << "\n";
        }
        return os;
    }
    
    void showMenu() {
        cout << "1. Display all products\n"
                  << "2. Add new product\n"
                  << "3. Remove product\n"
                  << "4. Edit product\n"
                  << "5. Search by name\n"
                  << "6. Search by price\n"
                  << "7. Exit\n"
                  << "Enter number: ";
    }
}
