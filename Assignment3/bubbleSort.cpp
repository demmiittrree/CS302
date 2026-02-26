#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;

// define bubble sort function
template <class T>
void LL<T>::bubbleSort() {
	// if there is one or less nodes
	if (this->head == nullptr || this->head->next == nullptr) {
		return;
	}

	// checks if there was a swap
	bool swapped = true;

	while (swapped) {
		// make swapped false in case list is sorted
		swapped = false;

		// use iterators to traverse list
		LL<T>::Iterator i(this->head);
		LL<T>::Iterator j(this->head->next);

		// go until j is nullptr
		while (j.current != nullptr) {
			// if data in i is greater than j
			if (i.current->data > j.current->data)  {
				// swap nodes
				swap(j, i);
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

	list.printList();
	list.bubbleSort();
	cout << endl;
	list.printList();

	return 0;
}
