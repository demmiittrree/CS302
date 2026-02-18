#include "LL.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	LL<string> list;
	bool turn = true;

	list.push_back("Homer");
	list.push_back("Bart");
	list.push_front("Maggie");
	list.push_front("Lisa");
	list.push_front("Marge");

	while (true)
	{
		if (turn)
		{	cout << "Before pop front: ";
			cout << list.front() << endl;
			list.pop_front();

			if (list.isEmpty())
				break;

			cout << "After pop front: ";
			cout << list.front() << endl;
		}
		else
		{
			cout << "Before pop back: ";
			cout << list.back() << endl;
			list.pop_back();

			if (list.isEmpty())
				break;

			cout << "After pop back: ";
			cout << list.back() << endl;	
		}
		
		cout << endl;
		turn = !turn;
	}


	return 0;
}