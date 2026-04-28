#include "priorityQ.h"

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ()
{
    capacity = 5;
    size = 0;
    heapArray = new priorityType[capacity];
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{
    // resize if needed
    if (size == capacity) {
        // double the capacity
        capacity *= 2;

        // make a new array with new capacity
        priorityType* newArray = new priorityType[capacity];

        // reallocate each index into the new array
        for (size_t i = 0 ; i < size ; ++i) {
            newArray[i] = heapArray[i];
        }
        
        // delete old heapArray
        delete[] heapArray;

        // allocate the new array with bigger capacity to heapArray
        heapArray = newArray;
    }
    
    // create new element
    priorityType newElement(key, priority);

    // put at the back of the heap array
    heapArray[size] = newElement;

    // update map
    itemToPQ[key] = size;

    // increment current size
    ++size;

    // call bubble up and pass index
    bubbleUp(size - 1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
    // check if theres nothing to pop
    if (size == 0) {
        return;
    }

    // remove root item from map
    itemToPQ.erase(heapArray[0].key);

    // overwrite root with element at index size
    heapArray[0] = heapArray[size-1];

    // dec size
    --size;

    // update map and bubble down
    if (size > 0) {
        itemToPQ[heapArray[0].key] = 0;
        bubbleDown(0);
    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::update_element(const t1& key, const t2& priority)
{
    // find index of item with key
    size_t index = itemToPQ.at(key);

    // store old priority to compare it later
    t2 old = heapArray[index].priority;

    // update priority to new priority parameter
    heapArray[index].priority = priority;

    // bubble up if new p is smaller
    if (priority < old) {
        bubbleUp(index);
    } 
    // bubble down if new p is greater
    else {
        bubbleDown(index);
    }
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
    // returns the priority value of the root item
    return heapArray[0].priority;
}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    // returns the key value of the root item
    return heapArray[0].key;
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_element(t1 key)
{
    size_t index = itemToPQ.at(key);

    // returns the lander with same key
    return heapArray[index].priority;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
    // if theres no elements in the heap array
    if (size == 0) {
        return true;
    }

    // if there are elements
    return false;
}


template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    while (index > 0) {
        // get index of parent
        size_t parent = (index - 1) / 2;

        // check if child has higher priority
        if (heapArray[index].priority < heapArray[parent].priority) {
            
            // SWAP parent and child

            // swap in array
            // save child information
            priorityType child = heapArray[index];
            // overwrite child with parent
            heapArray[index] = heapArray[parent];
            // overwrite parent with child
            heapArray[parent] = child;

            // swap in map
            itemToPQ[heapArray[index].key] = index;
            itemToPQ[heapArray[parent].key] = parent;


            // update index
            index = parent;
        } 
        // break out of while loop if in right place
        else {
            break;
        } 
    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    while (true) {
        // get index of left and right child
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        // use to see whichever has higher priority
        size_t check = index;
        
        // check child on left

        // make sure index is within array size, then check priority
        if (left < size && heapArray[left].priority < heapArray[check].priority) {
            check = left;
        }

        // check child on right against current priority
        if (right < size && heapArray[right].priority < heapArray[check].priority) {
            check = right;
        }

        // if neither child was a higher priority
        if (check == index) {
            break;
        }

        // else...
        // SWAP parent and child

        // swap in array
        // save child information
        priorityType child = heapArray[check];
        // overwrite child with parent
        heapArray[check] = heapArray[index];
        // overwrite parent with child
        heapArray[index] = child;

        // swap in map
        itemToPQ[heapArray[index].key] = index;
        itemToPQ[heapArray[check].key] = check;

        // update index
        index = check;    
    }
}

template class priorityQ<std::string, int>;
template class priorityQ<std::string, lander>;
