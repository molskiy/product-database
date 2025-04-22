#include "func.h"
#include <iostream>
using namespace std;

int main(){
    Shop::Database db("products.txt");
    int choice;

    do {
        Shop::showMenu();
        cin >> choice;

        switch (choice){
        case 1:
            db.displayAll();
            break;
        case 2:{
            Shop::Product p;
            cout << "enter product data (name, price, quantity): ";
            cin >> p;
            db.addProduct(p);
            break;
        }
        case 3:{
            int index;
            cout << "enter product number to remove: ";
            cin >> index;
            db.removeProduct(index - 1);
            break;
        }
        case 4:{
            int index;
            cout << "enter product number to edit: ";
            cin >> index;
            db.editProduct(index - 1);
            break;
        }
        case 5:{
            string name;
            cout << "enter name to search: ";
            cin >> name;
            db.searchByName(name);
            break;
        }
        case 6:{
            double price;
            cout << "enter maximum price: ";
            cin >> price;
            db.searchByPrice(price);
            break;
        }
        case 7:
            cout << "exiting..." << endl;
            break;
        default:
            cout << "invalid choice" << endl;
        }
    } while (choice != 7);

    return 0;
}
