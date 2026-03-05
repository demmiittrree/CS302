#include <cstdlib>
#include <string>

#ifndef BST_H
#define BST_H

template <class t1, class t2>
class bst
{
private:
  class binTreeNode
  {
  public:
    binTreeNode() : key( t1() ), value( t2() ), left(nullptr), right(nullptr) {}
    binTreeNode(t1 k, t2 v) : key(k), value(v), left(nullptr), right(nullptr) {}

    t1 key;
    t2 value;

    binTreeNode * left;
    binTreeNode * right;
  };

  binTreeNode * root;

  void deallocateTree(binTreeNode*);

  binTreeNode* insert(binTreeNode*, t1, t2);
  void update(binTreeNode*, t1, t2);
  t2 getValue(binTreeNode*, t1);


public:
  bst() : root(nullptr) {}
  ~bst() { deallocateTree(root); }
  void insert(t1 k, t2 v) { root = insert(root, k, v); }
  void update(t1 k, t2 v) { update(root, k, v); }
  t2 getValue(const t1& k) { return getValue(root, k); }
  std::string getPath(t1);
};

#endif
