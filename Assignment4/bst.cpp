#include "bst.h"
using std::string;

template <class t1, class t2>
// takes in root, call recursively to delete tree
void bst<t1, t2>::deallocateTree(binTreeNode * r)
{
    // if there's no node at root (no tree)
    if (r == nullptr) {
        return;
    }

    // deallocate left subtree recursively
    deallocateTree(r->left);
    // deallocate right subtree recursively
    deallocateTree(r->right);

    // delete root
    delete r;
}

template <class t1, class t2>
// takes in current node (starting from root), key, and value
typename bst<t1, t2>::binTreeNode* bst<t1, t2>::insert(binTreeNode * r, t1 k, t2 v)
{
    // when finding an empty leaf
    if (r == nullptr) {
        // create new node with key and value
        binTreeNode* newLeaf = new binTreeNode(k, v);
        return newLeaf;
    }
    
    // if key is less than r key
    if (k < r->key) {
        // move left in tree recursively
        r->left = insert(r->left, k, v);
    // if key is more than r key
    } else {
        // move right in tree recursively 
        r->right = insert(r->right, k, v);
    }

    // return upward
    return r;
}

template <class t1, class t2>
void bst<t1, t2>::update(binTreeNode * r, t1 k, t2 v)
{
    // if couldn't find the right node
    if (r == nullptr) {
        return;
    }
    // once at the right key
    if (r->key == k) {
        // update value
        r->value = v;
        return;
    }

    // recursively look for node with key == k
    if (k < r->key) {
        update(r->left, k, v);
    } else {
        update(r->right, k, v);
    }
}

template <class t1, class t2>
t2 bst<t1, t2>::getValue(binTreeNode * r, t1 k)
{
    // once at the right key
    if (r->key == k) {
        return r->value;
    }

    // recursively look for node with key == k
    if (k < r->key) {
        return getValue(r->left, k);
    } else {
        return getValue(r->right, k);
    }
}

template <class t1, class t2>
string bst<t1, t2>::getPath(t1 k)
{
    
}

template class bst<char, std::string>;
template class bst<std::string, char>;
