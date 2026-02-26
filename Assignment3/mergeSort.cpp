#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

// define split class
template <class T>
typename LL<T>::Node* LL<T>::split() {
	// check if there is one or less nodes
	if (this->head == nullptr || this->head->next == nullptr) {
		return this->head;
	}

	// create fast node that will reach end of list
	Node* fast = this->head;
	// create slow node that will reach middle of the list
	Node* slow = this->head;

	// make fast and slow traverse list
	while (fast != nullptr && fast != this->tail) {
		fast = fast->next->next;
		slow = slow->next;
	}

	// split the list into two different lists
	slow->prev->next = nullptr;
	slow->prev = nullptr;

	// return list #2's head
	return slow;
}


// define merge class
template <class T>
typename LL<T>::Node* LL<T>::merge(Node* first, Node* second) {
	// base call 
	// check if either list has no nodes, if so, return the other
	if (first == nullptr) {
		return second;
	}
	if (second == nullptr) {
		return first;
	}

	// find which node has a smaller value 
	if (first->data < second->data) {
		// recursive call to merge lists
		first->next = merge(first->next, second);
		// if there is a node in front of first
		if (first->next != nullptr) {
			// connect the nodes together
			first->next->prev = first;
		}
		// make sure there's no node before first
		// since it's the head
		first->prev = nullptr;
		return first;
	} 
	// if the second list is less than the first
	else {
		// recursive call to merge lists
		second->next = merge (first, second->next);
		// if there's a node in front of second
		if (second->next != nullptr) {
			// connect the nodes together
			second->next->prev = second;
		}
		// make sure there's no nodes before second
		// since it's the head
		second->prev = nullptr;
		return second;
	}
}

// define mergeSort class
template <class T>
typename LL<T>::Node* LL<T>::mergeSort() {
	// base call 
	// if the list has 1 or no nodes
	if (this->head == nullptr || this->head->next == nullptr) {
		return head;
	}

	// split the list into two
	Node* newHead = this->split();

	// make a new list and make newHead the head
	LL<T> newList;
	newList.head = newHead;

	// recursive call for each half (splits up lists) 
	this->head = mergeSort(head);
	newList.head = mergeSort(newHead);

	// merge and sort the halves
	return merge(head, newHead);
}

int main()
{
	LL<int> list;
	int x; // x is used to input data value in each node
	
	// populate the list
	while (cin >> x) { // this loop goes until file is done
		list.push_back(x); // add each node to the end
	}

	// merge sort list
	LL<int>::Node* sortedList = list.mergeSort(list.getHead());
	// make list head the new sorted list
	list.head = sortedList;
	
	// fix tail since the order was changed
	LL<int>::Node* fixTail = list.head;
	// go to end of list
	while (fixTail->next != nullptr) {
		fixTail = fixTail->next;
	}
	// update tail
	list.tail = fixTail;
	
	return 0;
}
