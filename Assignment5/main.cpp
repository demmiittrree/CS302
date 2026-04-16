#include "hashMap.h"
#include "menuType.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    hashMap<string, menuType> menu;
    vector<string> names;

    // get file name from user
    string fileName;
    cout << "Enter Krusty Krab Menu: ";
    cin >> fileName;
    cout << endl;
    // this thing was genuinely causing so many problems
    cin.ignore(1000, '\n');

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
        string originalName = line.substr(0, comma);
        name = originalName;
        // insert as fully lowercase to regulate
        for (int i = 0 ; i < name.length() ; ++i) {
            name[i] = tolower(name[i]);
        }
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
        menuType item(originalName, p, q);
        menu.insert(name, item);
        // add name to list of names
        names.push_back(name);
    }


    char choice = 'N';
    double total = 0;

    while (choice != 'Y') 
    {
        cout << endl;
        // make sure there are greater than 0 items left
        int itemsCount = 0;
        // need to print out hash map tables
        for (int i = 0 ; i < names.size() ; ++i) {
            // get the menuType item relating to the name at index
            menuType x = menu.getValue(names[i]);
            // dont print item if theres nothing left
            if (x.getQuantity() == 0) {
                ++itemsCount;
                continue;
            }
            // print item information
            cout << left << setw(45) << x.getName()
                 << right << setw(10) << fixed << setprecision(2) << x.getPrice()
                 << right << setw(10) << x.getQuantity() 
                 << endl;
        }
        // if ALL items are sold out
        if (itemsCount == names.size()) {
            choice = 'Y';
            continue;
        }
    
        // ask user what they want to order
        string order;
        cout << endl << "Hurry up and order something: ";        
        getline(cin, order);
        // make order completely lowercase for check
        for (int i = 0 ; i < order.length() ; ++i) {
            order[i] = tolower(order[i]);
        }

        // check if order is valid
        while (true) {
            // if the order name EXISTS
            if (menu.find(order)) {
                menuType y = menu.getValue(order);
                // make sure there's AT LEAST ONE of the order left
                if (y.getQuantity() > 0) {
                    break;
                }
            }

            // if the user entered an invalid item, prompt and loop
            cout << endl << "We serve food here..." << endl;
            cout << endl << "Hurry up and order something: ";
            getline(cin, order);
            cout << endl;

            for (int i = 0 ; i < order.length() ; ++i) {
                order[i] = tolower(order[i]);
            }
        }

        // ask user how much they want to order
        int amount = 0;
        cout << endl << "How much of this stuff do you want? ";
        cin >> amount;

        menuType x = menu.getValue(order);
        while (cin.fail() || amount > x.getQuantity()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << endl << "Ahem...can we please move this order along?" << endl;
            cout << endl << "How of this stuff do you want? ";
            cin >> amount;
        }

        // once user enters a valid quantity, update total
        total += x.getPrice()*amount;
        
        // change value to reflect how much was bought
        menuType z = menu.getValue(order);
        z.updateQuantity(amount);
        menu.update(order, z);

        // ask user if they're done
        cout << endl << "Will this complete your order...barnaclehead? ";
        cin >> choice;
        cin.ignore(1000,'\n');
    }

    cout << "Order Total " << total;

}
