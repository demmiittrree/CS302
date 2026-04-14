using namespace std;
#include "bst.h"
#include <iostream>
#include <fstream>

int main() {
    string lettersFile = "";
    string textFile = "";
    char choice = 'x';
    char ch;

    // take in file names and choice
    cin >> lettersFile >> textFile >> choice;
    ifstream lFile(lettersFile);

    bst<char, string> morseCodes;  // letter to morse code object
    bst<string, char> characters;  // morse code to letter objects
    

    // POPULATE THE MORSE CODES AND CHARACTERS

    // get first character
    lFile.get(ch);
    while (!lFile.eof())
    {
    // insert the character into the binary search tree
    morseCodes.insert(ch, "");
    
    // get path of character
    string value = morseCodes.getPath(ch);
    // update value of character
    morseCodes.update(ch, value);

    // insert into characters (path, character)
    characters.insert(value, ch);

    // skip the end of line delimeter
    lFile.get(ch);
    // read the character on the next line
    lFile.get(ch);
    }
    
    lFile.close();

    // open file with text
    ifstream tFile(textFile);

    // if choice is to encrypt
    if (choice == 'E' || choice == 'e') {
        string textLine;
        while (getline(tFile, textLine)) { // read each line
            for (int i = 0; i < textLine.length(); ++i) {
                // get the path of string[i]
                string encryptPath = morseCodes.getPath(textLine[i]);
                // print path, then a #
                cout << encryptPath << "#";
            }

            string newLine = morseCodes.getPath('\n');
            cout << newLine << "#";
        }
    }

    // if choice is to decrypt
    if (choice == 'D' || choice == 'd') {
        string textLine;
        while (getline(tFile, textLine)) { // read each line
            // go until the end of line
            string decryptPath = "";
            for (int i = 0; i < textLine.length(); ++i) {
                // if its not a hashtag (not done with path)
                if (textLine[i] != '#') {
                    decryptPath += textLine[i]; // add path direction to decrypt
                }
                // if it is a hashtag, decrypt, reset decryptPath, and print
                else { 
                    char decrypted = characters.getValue(decryptPath); // decrypt path to char
                    if (decrypted == '\n') {
                        cout << endl;
                    } else {
                        cout << decrypted;
                    }
                    
                    decryptPath = ""; // reset path
                }
            }
        }
    }
    
    tFile.close();
}