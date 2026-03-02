#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;

// implement a printList function to print sorted list
template <typename T>
void printList(LL<T>& list) {
	// use iterators to access list, go until end of list
	for (typename LL<T>::Iterator it = list.begin();
		it != nullptr; ++it) {
			// print value of iterator 
			cout << *it << " ";
    }
}

// define bubble sort function
template <typename T>
void bubbleSort(LL<T>& list) {
	// if there is one or less nodes
	if (list.isEmpty() || list.begin() == list.end()) {
		return;
	}

	// checks if there was a swap
	bool swapped = true;

	while (swapped) {
		// make swapped false in case list is sorted
		swapped = false;

		// use iterators to traverse list
		typename LL<T>::Iterator i = list.begin();
		typename LL<T>::Iterator j = list.begin();
		// make j one ahead of i
		++j;

		// go until j is nullptr
		while (j != nullptr) {
			// if data in i is greater than j
			if (*i > *j)  {
				// swap nodes
				list.swap(j,i);
				// make swapped true
				swapped = true;	
			}
			// increment iterators
			++i;
			++j;
		}
	}
}

int main()
{
	LL<int> list;
	int x;

	while (cin >> x)
		list.push_back(x);

	bubbleSort(list);
	printList(list);

	return 0;
}
