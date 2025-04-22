#include <string>
#include <iostream>
#include <fstream>
using namespace std;
namespace Shop{
    class Product{
    private:
        string name;
        double price;
        int quantity;
    public:
        Product();
        Product(string n, double p, int q);
        string getName() const;
        double getPrice() const;
        int getQuantity() const;
        void setName(string n);
        void setPrice(double p);
        void setQuantity(int q);
        void display() const;
        friend ostream& operator<<(ostream& os, const Product& p);
        friend istream& operator>>(istream& is, Product& p);
    };

    class Database{
    private:
        Product* products;
        int size;
        int capacity;
        string filename;
        void resize();
    public:
        Database(const string& fname);
        ~Database();
        void loadFromFile();
        void saveToFile();
        void displayAll() const;
        void addProduct(const Product& p);
        void removeProduct(int index);
        void editProduct(int index);
        void searchByName(const string& name) const;
        void searchByPrice(double maxPrice) const;
        friend ostream& operator<<(ostream& os, const Database& db);
    };
    void showMenu();
}
