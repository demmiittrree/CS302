#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

template <typename T>
void printList(typename LL<T>::Node* head) {
    // use node to traverse list
    typename LL<T>::Node* current = head;

    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
}

// define split class
template <typename T>
typename LL<T>::Node* split(typename LL<T>::Node* head) {
	// check if there is one or less nodes
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	// create fast node that will reach end of list
	typename LL<T>::Node* fast = head;
	// create slow node that will reach middle of the list
	typename LL<T>::Node* slow = head;

	// make fast and slow traverse list
	while (fast->next != nullptr && fast->next->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}

	// split
	// hold node after middle
	typename LL<T>::Node* temp = slow->next;
	// make middle node's next point to nothing
	slow->next = nullptr;
	// if theres a node after middle node
	if (temp != nullptr) {
		// make its previous = null
		temp->prev = nullptr;
	}

	// return list #2's head
	return temp;
}


// define merge class
template <class T>
typename LL<T>::Node* merge(typename LL<T>::Node* first, typename LL<T>::Node* second) {
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
		second->next = merge(first, second->next);
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
typename LL<T>::Node* mergeSort(typename LL<T>::Node* head) {
	// base call 
	// if the list has 1 or no nodes
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	// split the list into two
	typename LL<T>::Node* newHead = split(head);

	// recursive call for each half (splits up lists) 
	head = mergeSort(head);
	newHead = mergeSort(newHead);

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
	LL<int>::Node* sortedList = mergeSort<int>(list.head);
	// make list head equal to the new sorted list, starting from head
	list.head = sortedList;
	
	// fix tail since the order was changed
	LL<int>::Node* fixTail = list.head;
	// go to end of list
	while (fixTail->next != nullptr) {
		fixTail = fixTail->next;
	}
	// update tail
	list.tail = fixTail;

	// print sorted list
	printList<int>(list.head);
	
	return 0;
}
