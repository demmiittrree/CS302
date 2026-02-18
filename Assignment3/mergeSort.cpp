#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
using std::size_t;


// merge
void merge(LL<int>& list, int left, int mid, int right) {

}

// merge sort
void mergeSort(LL<int>& list, int left, int right) {
	// if there is one or less nodes in list
	if (left >= right) {
		return;
	}

}

template <class T>
int LL<T>::findMiddle(int right) {
	Node* a = head;
	Node* b = tail;
	int aCount = 1;
	int bCount = right; // right is nodeCount

	// goes until reaching middle point (or left/right middle)
	while (bCount > aCount) {
		a = a->next;
		b = b->prev;
		aCount++;
		bCount--;
	}

	return aCount;
}

int main()
{
	LL<int> list;
	
	int nodeCount = 0;
	int x; // x is used to input data value in each node
	
	// populate the list
	while (cin >> x) { // this loop goes until file is done
		list.push_back(x); // add each node to the end
		nodeCount++;
	}
	

	// add merge sort


	return 0;
}
