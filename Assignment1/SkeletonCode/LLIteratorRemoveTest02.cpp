#include "LL.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	LL<string> list;
	LL<string>::Iterator it, nil;

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

	it = list.begin();

	cout << "Iterator (Before Remove): " << *it << endl;

	list.removeNode(it);

	cout << "Iterator (After Remove): " << *it << endl;

	cout << endl;

	for (auto i = list.begin(); i != nil; i++)
		cout << *i << " ";

	cout << endl << endl;

	for (auto i = list.end(); i != nil; i--)
		cout << *i << " ";

	cout << endl << endl;



	return 0;
}
