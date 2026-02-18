#include "LL.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	LL<string> list;
	LL<string>::Iterator it;
	LL<string>::Iterator nil;

	list.push_back("Homer");
	list.push_back("Bart");
	list.push_front("Maggie");
	list.push_front("Lisa");
	list.push_front("Marge");
	list.push_front("Moe");
	list.push_front("Barney");
	list.push_front("Mr.Burns");
	list.push_back("ComicBookGuy");
	// mr burns barney moe marge lisa maggie homer bart comicbookguy

	// pass
	for (auto i = list.begin(); i != nil; i++)
		cout << *i << " ";

	cout << endl << endl;

	// pass
	for (auto i = list.end(); i != nil; i--)
		cout << *i << " ";

	cout << endl << endl;

	LL<string> list2(list);

	list.pop_front();
	list2.pop_back();

	// pass
	for (auto i = list.begin(); i != nil; i++)
		cout << *i << " ";

	cout << endl << endl;

	// pass
	for (auto i = list.end(); i != nil; i--)
		cout << *i << " ";

	cout << endl << endl;
	// pass
	for (auto i = list2.begin(); i != nil; i++)
		cout << *i << " ";

	cout << endl << endl;

	//pass
	for (auto i = list2.end(); i != nil; i--)
		cout << *i << " ";

	cout << endl << endl;

	list = list2;

	list.pop_front();
	list2.pop_back();

	for (auto i = list.begin(); i != nil; i++)
		cout << *i << " ";

	cout << endl << endl;

	for (auto i = list.end(); i != nil; i--)
		cout << *i << " ";

	cout << endl << endl;

	for (auto i = list2.begin(); i != nil; i++)
		cout << *i << " ";

	cout << endl << endl;

	for (auto i = list2.end(); i != nil; i--)
		cout << *i << " ";

	cout << endl << endl;

	return 0;

}
