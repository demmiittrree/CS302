#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

// define split class
template <class T>
typename LL<T>::Node* LL<T>::split(Node* head) {
	// create fast node that will reach end of list
	Node* fast = head;
	// create slow node that will reach middle of the list
	Node* slow = head;

	// make fast and slow traverse list
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}

	// make temp equal to node AFTER middle (or right-middle)
	Node* temp = slow->next;
	// split the list into two different lists
	slow->next = nullptr;
	
	// double checks that there is more than one node
	if (temp != nullptr) {
		// make temp (new list's head), not have a prev
		temp->prev = nullptr; 
	}

	// return list #2's head
	return temp;
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
typename LL<T>::Node* LL<T>::mergeSort(Node* head) {
	// base call 
	// if the list has 1 or no nodes
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	// split the list into two
	Node* newList = split(head);

	// recursive call for each half (splits up lists) 
	head = mergeSort(head);
	newList = mergeSort(newList);

	// merge and sort the halves
	return merge(head, newList);
}

int main()
{
	LL<int> list;
	int x; // x is used to input data value in each node
	
	// populate the list
	while (cin >> x) { // this loop goes until file is done
		list.push_back(x); // add each node to the end
	}

	// split the list
	list.mergeSort(list.getHead());

	return 0;
}
