#include "bst.h"
using std::string;

template <class t1, class t2>
void bst<t1, t2>::deallocateTree(binTreeNode * r)
{

}

template <class t1, class t2>
typename bst<t1, t2>::binTreeNode* bst<t1, t2>::insert(binTreeNode * r, t1 k, t2 v)
{

}

template <class t1, class t2>
void bst<t1, t2>::update(binTreeNode * r, t1 k, t2 v)
{

}

template <class t1, class t2>
t2 bst<t1, t2>::getValue(binTreeNode * r, t1 k)
{

}

template <class t1, class t2>
string bst<t1, t2>::getPath(t1 k)
{
  
}

template class bst<char, std::string>;
template class bst<std::string, char>;
