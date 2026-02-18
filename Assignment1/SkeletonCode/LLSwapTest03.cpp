#include "LL.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	LL<string> list;
	LL<string>::Iterator i, j, nil;

	list.push_back("Homer");
	list.push_back("Bart");
	list.push_front("Maggie");
	list.push_front("Lisa");
	list.push_front("Marge");
	list.push_front("Moe");
	list.push_front("Barney");
	list.push_front("Mr.Burns");
	list.push_back("ComicBookGuy");


	for (auto i = list.begin(); i != nil; i++)
		cout << *i << " ";

	cout << endl << endl;

	for (auto i = list.end(); i != nil; i--)
		cout << *i << " ";

	cout << endl << endl;



	i = j = list.begin();
	j++;

	cout << "Before Swap" << endl;
	cout << "i: " << *i << endl;
	cout << "j: " << *j << endl;

	list.swap(i, j);

	cout << endl;

	cout << "After Swap" << endl;
	cout << "i: " << *i << endl;
	cout << "j: " << *j << endl << endl;

	for (auto i = list.begin(); i != nil; i++)
		cout << *i << " ";

	cout << endl << endl;

	for (auto i = list.end(); i != nil; i--)
		cout << *i << " ";

	cout << endl;

	return 0;
}
