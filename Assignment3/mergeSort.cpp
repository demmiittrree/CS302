#include <iostream>
#include "LL.h"
using std::cin;
using std::cout;
using std::endl;

// global counter for comparisons
size_t comparisonCount = 0;

// print list (inclusive of tail)
template <typename T>
void printList(LL<T>& list) {
    typename LL<T>::Iterator last = list.end();
    for (typename LL<T>::Iterator it = list.begin(); ; ++it) {
        cout << *it << " ";
        if (it == last) break;
    }
    cout << endl;
}
template <typename T>
void merge(LL<T>& list, typename LL<T>::Iterator left, typename LL<T>::Iterator middle, typename LL<T>::Iterator right) {
    typename LL<T>::Iterator middleNext = middle;
    ++middleNext; // start of second half

    LL<T> temp;

    typename LL<T>::Iterator a = left;
    typename LL<T>::Iterator b = middleNext;

    // merge elements into temp
    while (true) {
        if (a == middleNext && b == right) {
            temp.push_back(*b); // push the last element
            break;
        } else if (a == middleNext) {
            temp.push_back(*b);
            if (b == right) break;
            ++b;
        } else if (b == nullptr) {  // just in case, safety check
            temp.push_back(*a);
            if (a == middle) break;
            ++a;
        } else {
            comparisonCount++;
            if (*a <= *b) {
                temp.push_back(*a);
                if (a == middle) break;
                ++a;
            } else {
                temp.push_back(*b);
                if (b == right) break;
                ++b;
            }
        }
    }

    // copy temp back using swap
    a = left;
    typename LL<T>::Iterator itTemp = temp.begin();
    while (true) {
        list.swap(a, itTemp);
        if (a == right) break;
        ++a;
        ++itTemp;
    }
}

// find middle iterator (slow/fast) inclusive of tail
template <typename T>
typename LL<T>::Iterator findMiddle(typename LL<T>::Iterator left, typename LL<T>::Iterator right) {
    typename LL<T>::Iterator slow = left;
    typename LL<T>::Iterator fast = left;

    typename LL<T>::Iterator fastNext = fast;
    ++fastNext;

    while (fastNext != right && fastNext != nullptr) {
        ++slow;
        ++fast;
        ++fastNext;
        if (fastNext != right && fastNext != nullptr) {
            ++fast;
            ++fastNext;
        }
    }
    return slow;
}

// recursive merge sort [left..right] inclusive
template <typename T>
void mergeSort(LL<T>& list, typename LL<T>::Iterator left, typename LL<T>::Iterator right) {
    if (left == right) return;

    typename LL<T>::Iterator middle = findMiddle<T>(left, right);
    typename LL<T>::Iterator middleNext = middle;
    ++middleNext;

    mergeSort(list, left, middle);
    mergeSort(list, middleNext, right);

    merge(list, left, middle, right);
}

int main() {
    LL<int> list;
    int x;
    while (cin >> x) list.push_back(x);

    typename LL<int>::Iterator left = list.begin();
    typename LL<int>::Iterator right = list.end();

    mergeSort(list, left, right);

    printList(list);

    cout << "Total comparisons: " << comparisonCount << endl;
}