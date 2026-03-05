#include "bst.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::tolower;

int main()
{
  bst<char, string> morseCodes;
  string filename;
  ifstream infile;
  char ch;

  cin >> filename;

  infile.open(filename);

  //get the first characger
  infile.get(ch);

  while (!infile.eof())
  {
    //insert the character into the binary search tree
    morseCodes.insert(ch, "");

    //skip the end of line delimeter
    infile.get(ch);

    //read the character on the next line
    infile.get(ch);
  }

  infile.close();

  for (char c = 'A'; c <= 'Z'; c++)
  {
    cout << c << ": " << morseCodes.getPath(c) << endl;
    cout << (char(tolower(c))) << ": " << morseCodes.getPath( tolower(c) ) << endl;
  }

  for (char c = '0'; c <= '9'; c++)
    cout << c << ": " << morseCodes.getPath(c) << endl;

  cout << "COMA: " << morseCodes.getPath(',') << endl;
  cout << "DOT: " << morseCodes.getPath('.') << endl;
  cout << "SPACE: " << morseCodes.getPath(' ') << endl;
  cout << "RET: " << morseCodes.getPath('\n') << endl;

  return 0;
}
