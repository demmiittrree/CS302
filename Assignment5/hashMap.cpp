#include "hashMap.h"
#include <cstdlib>
#include <string>
#include <cmath>
using std::string;
using std::size_t;

template <class t1, class t2>
hashMap<t1, t2>::hashMap(size_t initCapacity)
{
    // set variable values
    capacity = initCapacity;
    items1 = 0;
    items2 = 0;

    // allocate an array node*[capacity] to table1 and 2
    table1 = new node*[capacity];
    table2 = new node*[capacity];

    // set each element of tables with nullptr
    for (std::size_t i = 0 ; i < capacity ; ++i) {
        table1[i] = nullptr;
        table2[i] = nullptr;
    }
}

template <class t1, class t2>
hashMap<t1, t2>::~hashMap()
{
    // deallocate nodes in table1
    for (std::size_t i = 0 ; i < capacity ; ++i) {
        delete table1[i];
    }
    // deallocate nodes in table2
    for (std::size_t i = 0 ; i < capacity ; ++i) {
        delete table2[i];
    }
    
    // deallocate table 1 and table 2
    delete[] table1;
    delete[] table2;
}

template <class t1, class t2>
size_t hashMap<t1, t2>::hash1(string k)
{
    // create sum variable
    std::size_t sum = 0;

    // find sum using hash function 1
    for (int i = 0 ; i < k.length() ; ++i) {
        char current = k[i];
        sum += current * pow(10, i);
    }

    return sum;
}

template <class t1, class t2>
size_t hashMap<t1, t2>::hash2(string k)
{
    // create sum variable
    std::size_t sum = 0;

    // find sum using hash function 2
    for (int i = 0 ; i < k.length() ; ++i) {
        char current = k[i];
        std::size_t power = k.length()- i - 1;
        sum += current * pow(10, power);
    }

    return sum;
}


template <class t1, class t2>
void hashMap<t1, t2>::resize(size_t amount)
{
    // resize capacity
    capacity *= amount;

    
    node** temp1 = new node*[capacity];
    node** temp2 = new node*[capacity];

}

template <class t1, class t2>
size_t hashMap<t1, t2>::lookup(t1 k)
{
    // collision counter
    std::size_t i = 0;

    // look for vacant slot
    while (true) {
        std::size_t index = (hash1(k) + i * hash2(k)) % capacity;
    
        // check table1 for vacant or match

        // if the location is vacant, return the index,
        if (table1[index] == nullptr) {
            return index;
        }
        // if this location is not vacant but the node in this location has a matching key, 
        // return the index.
        if (table1[index]->key == k) {
            return index;
        }

        // check table 2 for vacant or match

        // if the location is vacant, return the index,
        if (table2[index] == nullptr) {
            return index;
        }
        // if this location is not vacant but the node in this location has a matching key, 
        // return the index.
        if (table2[index]->key == k) {
            return index;
        }

        // if there's no match
        ++i;

        // if there is no slots available at all
        if (i >= capacity) {
            return capacity;
        }
    }
}
    

template <class t1, class t2>
bool hashMap<t1, t2>::find(t1 k)
{
    // since i made a check at the end for i >= capacity
    std::size_t found = lookup(k);
    
    // if found value is greater than capacity, wasn't found
    if (found >= capacity) {
        return false;
    } else {
        return true;
    }
}

template <class t1, class t2>
void hashMap<t1, t2>::insert(t1 k, t2 v)
{
    
    // load factor is number of currently stored / total size of hash table
    // since there's two tables, add up items and 2*capacity of tables
    double loadFactor = (items1 + items2) / (2.0 * capacity);

    // if load factor reaches 20%, resize tables x2
    if (loadFactor >= .20) {
        resize(2);
    }
    
    // insert node into hash map
    
    // create new node with k and v
    node* insert = new node(k, v);
    
    for (std::size_t i = 0 ; i < capacity ; ++i) {
        // location in table 1
        std::size_t location1 = hash1(k);
        // if location is not taken
        if (table1[location1] == nullptr) {
            // assign at location
            table1[location1] = insert;
            // increment count of items in t1
            ++items1;

            return;
        }

        // if location was taken
        
        // keep info on node being kicked
        node* temp = table1[location1];
        // replace kicked node with inserted node
        table1[location1] = insert;
        // prepare to insert kicked node into t2
        insert = temp;

        // location in table 2
        std::size_t location2 = hash2(insert->key);
        if (table2[location2] == nullptr) {
            table2[location2] = insert;
            ++items2;
            return;
        }

        // if location is taken in t2
        
    }

    
}

    
    
    

template <class t1, class t2>
void hashMap<t1, t2>::update(t1 k, t2 v)
{

}

template <class t1, class t2>
t2 hashMap<t1, t2>::getValue(t1 k)
{
	
}


template class hashMap<string, int>;
template class hashMap<string, string>;
template class hashMap<string, bool>;
template class hashMap<string, menuType>;
