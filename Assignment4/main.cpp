using namespace std;
#include "bst.h"
#include <iostream>
#include <fstream>

int main() {
    string lettersFile = "";
    string textFile = "";
    char choice = 'x';

    // take in file names and choice
    cin >> lettersFile >> textFile >> choice;
    ifstream lFile(lettersFile);
    if (!lFile.is_open()) { // check if open worked
        cout << "Opening letters file failed";
    }
    ifstream tFile(textFile);
    if (!tFile.is_open()) { // check if open worked
        cout << "Opening text file failed";
    }

    // letter to morse code object
    bst<char, string> bstObj;
    string line = "";   // string to get line
    // go through the letters file and update search tree
    while (getline(lFile, line)) {
        // get character of line
        char c = line[0];
        
        // insert character into bst
        bstObj.insert(c, "");            // insert w blank string
        string path = bstObj.getPath(c); // get path of node
        bstObj.update(c, path);          // update value of node with path
    }
    
    // if choice is to encrypt
    if (choice == 'E' || choice == 'e') {
        string textLine;
        while (getline(tFile, textLine)) { // read each line
            for (int i = 0; i < textLine.length(); ++i) {
                if (textLine[i] == ' ') {
                    cout << "#";
                } else {
                    // get the path of string[i]
                    string encryptPath = bstObj.getPath(textLine[i]);
                    cout << encryptPath;
                }
            }
        }
    }

    // if choice is to decrypt

    
    //bst<string, char> bstObj2;
    //while (getline(tFile))
}