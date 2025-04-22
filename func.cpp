#include "func.h"
#include <iostream>
#include <fstream>
using namespace std;
namespace Shop{
    Product::Product(): name(""), price(0.0), quantity(0){}
    Product::Product(string n, double p, int q): name(n), price(p), quantity(q){}
    string Product::getName() const {return name;}
    double Product::getPrice() const {return price;}
    int Product::getQuantity() const {return quantity;}
    void Product::setName(string n) {name = n;}
    void Product::setPrice(double p) {price = p;}
    void Product::setQuantity(int q) {quantity = q;}
    void Product::display() const{
        cout << *this;
    }
    ostream& operator<<(ostream& os, const Product& p){
        os << p.name << " " << p.price << " " << p.quantity;
        return os;
    }
    istream& operator>>(istream& is, Product& p){
        is >> p.name >> p.price >> p.quantity;
        return is;
    }

    Database::Database(const string& fname): filename(fname), size(0), capacity(2){
        products = new Product[capacity];
        loadFromFile();
    }

    Database::~Database(){
        saveToFile();
        delete[] products;
    }

    void Database::resize(){
        capacity *= 2;
        Product* newProducts = new Product[capacity];
        for (int i = 0; i < size; ++i){
            newProducts[i] = products[i];
        }
        delete[] products;
        products = newProducts;
    }

    void Database::loadFromFile(){
        ifstream inFile(filename);
        if (inFile.is_open()){
            Product p;
            while (inFile >> p){
                addProduct(p);
            }
            inFile.close();
        }
        else{
            cerr << "can't open the file for reading." << endl;
        }
    }

    void Database::saveToFile(){
        ofstream outFile(filename);
        if (outFile.is_open()){
            for (int i = 0; i < size; ++i){
                outFile << products[i] << endl;
            }
            outFile.close();
        }
        else{
            cerr << "can't open file for writing." << endl;
        }
    }

    void Database::displayAll() const{
        for (int i = 0; i < size; ++i){
            products[i].display();
            cout << endl;
        }
    }

    void Database::addProduct(const Product& p){
        if (size >= capacity){
            resize();
        }
        products[size++] = p;
    }

    void Database::removeProduct(int index){
        if (index >= 0 && index < size){
            for (int i = index; i < size - 1; ++i){
                products[i] = products[i + 1];
            }
            --size;
        }
        else{
            cerr << "index out of range" << endl;
        }
    }

    void Database::editProduct(int index){
        if (index >= 0 && index < size){
            cout << "add new data for product:" << endl;
            Product newProduct;
            cin >> newProduct;
            products[index] = newProduct;
        }
        else{
            cerr << "index out of range" << endl;
        }
    }


    void Database::searchByName(const string& name) const{
        for (int i = 0; i < size; ++i){
            if (products[i].getName() == name){
                products[i].display();
                cout << endl;
            }
        }
    }

    void Database::searchByPrice(double maxPrice) const{
        for (int i = 0; i < size; ++i){
            if (products[i].getPrice() <= maxPrice){
                products[i].display();
                cout << endl;
            }
        }
    }
    ostream& operator<<(ostream& os, const Database& db){
        for (int i = 0; i < db.size; ++i){
            os << db.products[i] << endl;
        }
        return os;
    }
    void showMenu(){
        cout << "1. show products" << endl;
        cout << "2. add product" << endl;
        cout << "3. change product" << endl;
        cout << "4. delete product" << endl;
        cout << "5. search by name" << endl;
        cout << "6. search by price" << endl;
        cout << "7. exit" << endl;
    }
}
