/*
    Name: Demitre Lester, NSHE_ID_#2002641576, 1004, Assignment 1
    Description: This program is used to implement the linked 
                 list class. It implements constructors, the 
                 destructor, push functions, pop functions
    Input: There is no user input for this program
    Output: The program allows the user to manipulate their
            linked list by adding, removing, or changing nodes
*/

#include "LL.h"
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
LL<T>::LL()
{
    // make head and tail null
    head = nullptr;
    tail = nullptr;
}

template <class T>
LL<T>::LL(const LL<T>& copy)
{
    // check if copy list is empty
    if (copy.head == nullptr) {
        this->head = nullptr;
        this->tail = nullptr;
        return;
    }
    
    // if list is not empty,
    // create an iterator to go through copy list
    Iterator it(copy.head);

    // go until tail
    while (it.current != nullptr) {
        T tempData = it.current->data;
        push_back(tempData);
        it++;
    }
}

// equals operator for Linked List
template <class T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs)
{
    // if comparing list to itself
    if (this == &rhs) {
        return *this;
    }

    // delete nodes in this list
    
    // start at this head
    Iterator deleteNode(this->head);
    
    // go through this list and delete all nodes
    while (deleteNode.current != nullptr) {
        Node* temp = deleteNode.current->next;
        delete deleteNode.current;
        deleteNode.current = temp;
    }
    // make head and tail null so no garbage memory
    this->head = nullptr;
    this->tail = nullptr;

    // create an iterator to go through rhs list
    Iterator it(rhs.head);

    // go until tail
    while (it.current != nullptr) {
        T tempData = it.current->data;
        push_back(tempData);
        it++;
    }

    // return this list
    return *this;
}

// destructor for Linked List
template <class T>
LL<T>::~LL()
{
    // to go through list
    Node* current = head;
    
    // loop until end of list, deleting all nodes
    while (current != nullptr) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }

    // make head and tail null
    head = nullptr;
    tail = nullptr;
}

// add a node to the front
template <class T>
void LL<T>::push_front(const T& item)
{
    Node* push = new Node(); // node being pushed
    
    // if the list is empty
    if (head == nullptr) {
        push->data = item; // give data
        // make head and tail both new node
        head = push;
        tail = push;
        // make the next and previous both null
        push->next = nullptr;
        push->prev = nullptr;
        return;
    }

    push->data = item; // give data
    head->prev = push; // make the node before head, push
    push->next = head; // make next node old head
    push->prev = nullptr;
    head = push; // make head new node
}

// add a node to the end
template <class T>
void LL<T>::push_back(const T& item)
{
    Node* push = new Node(); // node being pushed

    // if the list is empty
    if (head == nullptr) {
        push->data = item; // give data
        // make head and tail both new node
        head = push;
        tail = push;
        // make the next and previous both null
        push->next = nullptr;
        push->prev = nullptr;
        return;
    }

    push->data = item; // give data
    tail->next = push; // make node after old tail, push
    push->prev = tail; // make tail the node before push
    push->next = nullptr;
    tail = push; // make tail new node
}

template <class T>
void LL<T>::pop_front()
{
    // if list is empty
    if (head == nullptr) {
        return;
    }

    // check if theres only one node
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    
    // make next node head
    head = head->next; 
    // delete old head
    delete head->prev;
    // make new head's prev, null
    head->prev = nullptr;
}

template <class T>
void LL<T>::pop_back()
{
    // if list is empty
    if (head == nullptr) {
        return;
    }

    // check if theres only one node
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }

    // make tail node before tail
    tail = tail->prev;
    // delete old tail
    delete tail->next;
    // make new tail's next, null
    tail->next = nullptr;
}

// remove node pointed to by it
template <class T>
void LL<T>::removeNode(LL<T>::Iterator& it)
{
    // if pointing to no node
    if (it.current == nullptr) {
        return;
    }
    
    // if theres only one node, or if its the head
    if (head == tail || it.current == head) {
        pop_front();
        it.current = head;
        return;
    }

    // if it is the tail
    if (it.current == tail) {
        pop_back();
        it.current = tail;
        return;
    }

    // keep track of node after it
    Node* temp = it.current->next;
    
    // if not head or tail, rearrange
    it.current->prev->next = it.current->next;
    it.current->next->prev = it.current->prev;
    
    // delete node before it, since incremented
    delete it.current;
    // update it
    it.current = temp;

}

template <class T>
void LL<T>::insertNode(const LL<T>::Iterator& it, const T& item)
{
    // if inserting at list tail
    if (it.current == tail) {
        push_back(item);
        return;
    }

    // create node to insert with item
    Node* insert = new Node(item);
    // rearrange pointers of currents previous and next
    it.current->next->prev = insert;
    insert->next = it.current->next;
    insert->prev = it.current;
    it.current->next = insert;
}

template <class T>
void LL<T>::swap(LL<T>::Iterator& i, LL<T>::Iterator& j)
{
    // make sure not swapping same nodes
    if (i.current == j.current) {
        return;
    }
    // make sure not null
    if (i.current == nullptr || j.current == nullptr) {
        return;
    }

    // use nodes for my sanity
    Node* first = i.current;
    Node* second = j.current;

    // save prev and next of nodes being swapped
    Node* firstPrev = first->prev;
    Node* firstNext = first->next;
    Node* secondPrev = second->prev;
    Node* secondNext = second->next;

    // check if first->next is second
    if (firstNext == second) {
        // rewire neighboring nodes 

        // check if first is head
        if (firstPrev == nullptr) {
            head = second;
        } else {
            firstPrev->next = second;
        }
        // check if second is tail
        if (secondNext == nullptr) {
            tail = first;
        } else {
            secondNext->prev = first;
        }
        
        // rewire swapped nodes
        first->next = secondNext;
        second->next = first;
        first->prev = second;
        second->prev = firstPrev;
    } 
    // do the same thing but with second being before first
    else if (secondNext == first) {
        if (secondPrev == nullptr) {
            head = first;
        } else {
            secondPrev->next = first;
        }
        if (firstNext == nullptr) {
            tail = second;
        } else {
            firstNext->prev = second;
        }
        
        second->next = firstNext;
        first->next = second;
        second->prev = first;
        first->prev = secondPrev;
    }
    // if the nodes arent next to each other
    else {
        // rewire neighbors
        if (firstPrev != nullptr) {
            firstPrev->next = second;
        }
        if (firstNext != nullptr) {
            firstNext->prev = second;
        }
        if (secondPrev != nullptr) {
            secondPrev->next = first;
        }
        if (secondNext != nullptr) {
            secondNext->prev = first;
        }

        // check if nodes were head or tail
        if (firstPrev == nullptr) {
            head = second;
        }
        if (firstNext == nullptr) {
            tail = second;
        }
        if (secondPrev == nullptr) {
            head = first;
        }
        if (secondNext == nullptr) {
            tail = first;
        }

        // rewire swapped nodes
        first->next = secondNext;
        second->next = firstNext;
        first->prev = secondPrev;
        second->prev = firstPrev;

    }
}


template <class T>
void LL<T>::printList() {
    // use node to traverse list
    Node* current = head;

    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
}

template class LL<int>;
template class LL<std::string>;
