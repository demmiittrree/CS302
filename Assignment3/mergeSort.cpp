#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
using std::size_t;


int main()
{
	LL<int> list;
	int x; // x is used to input data value in each node
	
	// populate the list
	while (cin >> x) { // this loop goes until file is done
		list.push_back(x); // add each node to the end
	}
	

	// add merge sort


	return 0;
}
