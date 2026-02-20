#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;

// define bubble sort function
template <class T>
void LL<T>::bubbleSort(LL &list) {
	// if there is one or less nodes
	if (list.head == nullptr || list.head->next == nullptr) {
		return list.head;
	}

	// checks if there was a swap
	bool swapped = true;
	// used to decrement list check after each go
	Node* lastSorted = list.tail;

	while (swapped) {
		// use iterators to traverse list
		LL<T>::Iterator i(list.head);
		LL<T>::Iterator j(list.head->next);
		
		// make swapped false in case list is sorted
		swapped = false;
	
		// go until iterator j reaches the last sorted node
		while (j.current != lastSorted->next) {
			// if data in j is less than data in i
			if (*j < *i)  {
				// swap nodes
				list.swap(i,j);
				// make swapped true
				swapped = true;
			}
			// increment iterators 1 node forward
			i++;
			j++;
		}

		// down by one after each loop
		lastSorted = lastSorted->prev;
	}
}

int main()
{
	LL<int> list;
	int x;

	while (cin >> x)
		list.push_back(x);

	list.bubbleSort(list);

	return 0;
}
