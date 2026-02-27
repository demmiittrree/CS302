#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

template <typename T>
void printList(LL<T>& list) {
	
	// use iterators to access list, go until end of list
	for (typename LL<T>::Iterator it = list.begin();
		it != typename LL<T>::Iterator(nullptr); ++it) {
			// print value of iterator 
			cout << *it << " ";

	}
}

// define middle function
template <typename T>
typename LL<T>::Iterator middle(typename LL<T>::Iterator begin,
                                typename LL<T>::Iterator end) {
    typename LL<T>::Iterator slow = begin;
    typename LL<T>::Iterator fast = begin;
    typename LL<T>::Iterator null;  // sentinel for end

    while (fast != end) {
        ++fast;
        if (fast == end) break;
        ++fast;
        ++slow;
    }

    return slow;
}


// define merge function
template <typename T>
void merge(typename LL<T>::Iterator begin, 
							typename LL<T>::Iterator end,
							typename LL<T>::Iterator middle,
							LL<T>& list) {
 	typename LL<T>::Iterator left = begin;

    while (left != middle) {
        typename LL<T>::Iterator minIt = left;
        typename LL<T>::Iterator it = middle;

        while (it != end) {
            if (*it < *minIt) {
                minIt = it;
            }
            ++it;
        }

        if (*minIt < *left) {
			list.swap(minIt, left);  // use your existing iterator swap
        }

        ++left;
    }
}

// define mergeSort function
template <typename T>
void mergeSort(typename LL<T>::Iterator begin,
                        typename LL<T>::Iterator end,
                        LL<T>& list) {   // pass list so you can call swap
	if (begin == end) return;  // empty range

	typename LL<T>::Iterator mid = middle<T>(begin, end);  // get middle
	if (mid == begin) return; // single element, stop recursion

	mergeSort<T>(begin, mid, list);
	mergeSort<T>(mid, end, list);

	merge<T>(begin, end, mid, list); // merge left and right
}

int main()
{
	LL<int> list;
	int x; // x is used to input data value in each node
	
	while (cin >> x)
		list.push_back(x);

	typename LL<int>::Iterator begin = list.begin();
    typename LL<int>::Iterator null; // sentinel for end

    mergeSort<int>(begin, list.end(), list);

    printList<int>(list);
}
