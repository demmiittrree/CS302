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
    // deallocate nodes in table1 and 2
    for (std::size_t i = 0 ; i < capacity ; ++i) {
        if (table1[i] != nullptr) {
            delete table1[i];
        }
        if (table2[i] != nullptr) {
            delete table2[i];
        }
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
        sum += k[i] * pow(10, i);
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
        std::size_t power = k.length()- i - 1;
        sum += k[i] * pow(10, power);
    }

    return sum;
}


template <class t1, class t2>
void hashMap<t1, t2>::resize(size_t amount)
{
    // resize capacity
    std::size_t oldCapacity = capacity;
    capacity *= amount;

    // save pointer to old tables
    node** old1 = table1;
    node** old2 = table2;

    // have old pointers point to bigger tables
    table1 = new node*[capacity];
    table2 = new node*[capacity];
    
    // set each element of new tables with nullptr
    for (std::size_t i = 0 ; i < capacity ; ++i) {
        table1[i] = nullptr;
        table2[i] = nullptr;
    }

    // reset amount of items in tables
    items1 = 0;
    items2 = 0;

    // go through old table1 and insert all elements into new tables
    for (int i = 0 ; i < oldCapacity ; ++i) {
        // if the slot is not empty
        if (old1[i] != nullptr) {
            insert(old1[i]->key, old1[i]->value);
        }

        // if the slot is not empty
        if (old2[i] != nullptr) {
            insert(old2[i]->key, old2[i]->value);
        }
    }

    // delete the old tables
    for (std::size_t i = 0 ; i < oldCapacity ; ++i) {
        if (old1[i] != nullptr) {
            delete old1[i];
        }
        if (old2[i] != nullptr) {
            delete old2[i];
        }
    }

    // deallocate table 1 and table 2
    delete[] old1;
    delete[] old2;
}

template <class t1, class t2>
size_t hashMap<t1, t2>::lookup(t1 k)
{
    // collision counter
    std::size_t i = 0;

    // look for vacant slot
    while (true) {
        std::size_t index = (hash1(k) + i * hash2(k)) % capacity;
    
        // check table1 for a match
        if (table1[index] != nullptr && table1[index]->key == k) {
            return index;
        }
        // check table2 for a match
        if (table2[index] != nullptr && table2[index]->key == k) {
            return index;
        }
        // check table1 for empty slot
        if (table1[index] == nullptr) {
            return index;
        }
        // check table2 for empty slot
        if (table2[index] == nullptr) {
            return index;
        }
        
        // if there's no match or empty slot
        ++i;

        // just in case there's no possible matches at all
        if (i >= capacity) {
            return capacity;
        }
    }
}
    

template <class t1, class t2>
bool hashMap<t1, t2>::find(t1 k)
{
    std::size_t i = 0;

    // look for match
    while (true) {
        std::size_t index = (hash1(k) + i * hash2(k)) % capacity;
    
        // check table1 for a match
        if (table1[index] != nullptr && table1[index]->key == k) {
            return true;
        }
        // check table2 for a match
        if (table2[index] != nullptr && table2[index]->key == k) {
            return true;
        }
        
        // if there's no match
        ++i;

        // if no match at all
        if (i >= capacity) {
            return false;
        }
    }
}

template <class t1, class t2>
void hashMap<t1, t2>::insert(t1 k, t2 v)
{
    
    // insert node into hash map
    
    // create new node with k and v
    node* insert = new node(k, v);
    
    // find index of where to insert node
    std::size_t index = lookup(k);

    // if k is in table 1
    if (table1[index] != nullptr && table1[index]->key == k) {
        return;
    } 
    // if k is in table 2
    else if (table2[index]->key == k && table2[index] != nullptr) 
    {
        return;
    }
    // if table 1 is empty
    if (table1[index] == nullptr) {
        table1[index] = insert;
        ++items1;
    }
    // if table 2 is empty
    else if (table2[index] == nullptr) {
        table2[index] = insert;
        ++items2;
    }

    // if either load factor goes over .2
    double loadFactor1 = static_cast<double>(items2 / capacity);
    double loadFactor2 = static_cast<double>(items2 / capacity);

    // if load factor reaches 20%, resize tables x2
    if (loadFactor1 >= .20 || loadFactor2 >= .20) {
        resize(2);
    }
}

template <class t1, class t2>
void hashMap<t1, t2>::update(t1 k, t2 v)
{
    // find index of the key
    std::size_t index = lookup(k);

    // check if invalid index
    if (index == capacity) {
        return;
    }

    // if index was for table 1
    if (table1[index] != nullptr && table1[index]->key == k) {
        table1[index]->value = v;
    } 
    // if index was for table 2
    else if (table2[index] != nullptr && table2[index]->key == k) 
    {
        table2[index]->value = v;
    }
    
}

template <class t1, class t2>
t2 hashMap<t1, t2>::getValue(t1 k)
{
	// find index of the key
    std::size_t index = lookup(k);

    // checks if out of bounds
    if (index == capacity) {
        return t2{};
    }

    // if index was for table 1
    if (table1[index] != nullptr && table1[index]->key == k) {
        // insert node at index in t1
        return table1[index]->value;
    } 
    // if index was for table 2
    else if (table2[index] != nullptr && table2[index]->key == k) 
    {
        // insert node at index in t2
        return table2[index]->value;
    }

    return t2{};
}


template class hashMap<string, int>;
template class hashMap<string, string>;
template class hashMap<string, bool>;
template class hashMap<string, menuType>;
