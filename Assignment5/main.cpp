#include "hashMap.h"
#include "menuType.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    hashMap<string, menuType> menu;
    vector<string> names;

    // get file name from user
    string fileName;
    cout << "Enter Krusty Krab Menu: ";
    cin >> fileName;

    // read through csv and tokenize each line
    // populate the menu map object
    ifstream iFile(fileName);

    // read into file, separate by the commas
    // must use substr, find, and erase
    // update hashMap by inserting each line
    string line;
    // skip past the first line
    getline(iFile, line);
    while (getline(iFile, line)) { 
        string name;
        string price;
        string quantity;

        // find where first comma is
        size_t comma = line.find(',');
        // name = line[0] to to before comma
        name = line.substr(0, comma);
        // remove from line up to comma
        line.erase(0,comma + 1);

        // find where second comma is
        comma = line.find(',');
        // price = after first comma to before second comma
        price = line.substr(0, comma);
        // remove from line up to second comma
        line.erase(0, comma + 1);

        // remainder of the line is just the quantity
        quantity = line;

        // make price and quantity equal to actual numbers
        double p = stod(price);
        int q = stoi(quantity);

        // make a menuType item with name, price, and quantity
        menuType item(name, p, q);
        menu.insert(name, item);
        // add name to list of names
        names.push_back(name);
    }


    char choice = 'N';

    while (choice != 'Y') 
    {

    
        // need to print out hash map tables
        for (int i = 0 ; i < names.size() ; ++i) {
            // get the menuType item relating to the name at index
            menuType x = menu.getValue(names[i]);

            // print item information
            cout << x.getName() << " "
                << x.getPrice() << " "
                << x.getQuantity() << endl;
        }
    
        // ask user what they want to order
        string order;
        cout << "Hurry up and order something: ";
        cin >> order;

        // ask user how much they want to order
        int amount = 0;
        while (true) {
            cout << "How much of this stuff do you want? ";
            cin >> amount;

            menuType x = menu.getValue(order);
        
            // if the user enters a valid quantity, leave loop
            if (amount <= x.getQuantity()) {
                break;
            }

            cout << "Ahem...can we please move this order along?";
        }   
        
        // change value to reflect how much was bought
        menuType x = menu.getValue(order);
        x.updateQuantity(amount);
        menu.update(order, x);

        // ask user if they're done
        cout << "Will this complete your order...barnaclehead? ";
        cin >> choice;

    }

}
