#include "LL.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	LL<string> list;
	LL<string>::Iterator nil;

	list.push_back("Homer");
	list.push_back("Bart");
	list.push_front("Maggie");
	list.push_front("Lisa");
	list.push_front("Marge");

	for (auto it = list.begin(); it != nil; it++)
		cout << *it << " ";

	cout << endl << endl;

	for (auto it = list.end(); it != nil; it--)
		cout << *it << " ";

	cout << endl;

	return 0;
}
