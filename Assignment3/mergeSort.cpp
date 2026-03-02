#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

// implement a print list function to print sorted list
template <typename T>
void printList(LL<T>& list) {
	// use iterators to access list, go until end of list
	typename LL<T>::Iterator null;
    for (typename LL<T>::Iterator it = list.begin();
		it != null; ++it) {
			// print value of iterator 
			cout << *it << " ";
    }
}

// define merge function
template <typename T>
void merge(LL<T>& list, 
        typename LL<T>::Iterator left, 
        typename LL<T>::Iterator right, 
        typename LL<T>::Iterator middle)
{
    // create iterator at start of first sublist, and start of second sublist
    typename LL<T>::Iterator a = left;
    typename LL<T>::Iterator b = middle;
    ++b;

    // use for loop conditions
    typename LL<T>::Iterator beyondMiddle = middle;
    ++beyondMiddle;
    typename LL<T>::Iterator beyondRight = right;
    ++beyondRight;
    
    LL<T> temp;

    // go until one goes beyond their bound
    while (a != beyondMiddle && b != beyondRight) {    
        if (*a <= *b) {
            temp.push_back(*a);
            ++a;
        } else {
            temp.push_back(*b);
            ++b;
        }
    }

    // remaining elements
    while (a != beyondMiddle) {
        temp.push_back(*a);
        ++a;
    }
    while (b != beyondRight) {
        temp.push_back(*b);
        ++b;
    }

    printList(temp);
    cout << endl;
    // need to copy the values of temp into list
    // AT range of left to right
    
    // start of range in original list
    typename LL<T>::Iterator i = left;
    // start of range in sub list
    typename LL<T>::Iterator j = temp.begin();

    // while i doesn't go out of range
    while (i != beyondRight) {
        // insert sorted node
        list.insertNode(i, *j);
        ++j; // increment j to next node

        list.removeNode(i);
        ++i;
    }
}

// define mergeSort function
template <typename T>
void mergeSort(LL<T>& list, 
                typename LL<T>::Iterator left, 
                typename LL<T>::Iterator right) 
{
    // if theres only one node in a sublist
    if (left == right) {
        return;
    }
    
    // first, find the node AFTER middle 
    
    typename LL<T>::Iterator temp = left; // use temp to go through list
    
    int count = 1; // count is ALLOWED here because the video said so haha
    
    // traverse list until end
    while (temp != right) {
        ++count;
        ++temp;
    }

    // find middle index
    int middleCount = count/2;
    // reset variables
    temp = left; 
    
    for (int i = 0; i < middleCount; ++i) {
        ++temp;
    }
    
    typename LL<T>::Iterator middle = temp;
    typename LL<T>::Iterator rightStart = middle;
    ++rightStart;

    // merge sort LEFTmost 
    mergeSort(list, left, middle);
    //merge sort RIGHTmost
    mergeSort(list, rightStart, right);
  
    // implement merge
    merge(list, left, right, temp);
}


int main()
{
	LL<int> list;
	int x; // x is used to input data value in each node
	
	while (cin >> x)
		list.push_back(x);

    typename LL<int>::Iterator left = list.begin();
    typename LL<int>::Iterator right = list.end();
    mergeSort(list, left, right);
    printList(list);
}
