#include "treap.h"

// Class Treap -> private -> Struct Node -> ...
//

trh::Treap::Node::Node(): Node(0) {}

trh::Treap::Node::Node(int key): Node(key, nullptr, nullptr){}

trh::Treap::Node::Node(int key, Node *left, Node *right): _x(key), _left(left), _right(right) 
{ 
  _y = rand() % INT32_MAX;
}

// Class Treap -> private -> ...
//

trh::Treap::Node *trh::Treap::merge(Node *a, Node *b)
{
  if(!a || !b)
    return a ? a : b;

  if (a->_y > b->_y)
  {
    a->_right = merge(a->_right, b);
    return a;
  }
  else
  {
    b->_left = merge(a, b->_left);
    return b;
  }
}

void trh::Treap::split(Node* n, int key, Node *&a, Node *&b)
{
  if(!n)
  {
    a = b = n;
    return;
  }
  
  if (n->_x < key)
  {
    split(n->_right, key, n->_right, b);
    a = n;
  }
  else{
    split(n->_left, key, a, n->_left);
    b = n;
  }  
}

void trh::Treap::deleteBranch(Node *n)
{
  Node* left = n->_left;
  Node* right = n->_right;
  delete n;

  if(left)
    deleteBranch(left);

  if(right)
    deleteBranch(right);
}

//Class Treap -> public -> ...
//

trh::Treap::Treap() : _root(nullptr) {}

void trh::Treap::insert(int key)
{
  Node *less, *greated;

  split(_root, key, less, greated);
  less = merge(less, new Node(key));
  _root = merge(less, greated);
}

bool trh::Treap::contains(int key)
{  
  Node *tmp = _root;

  while(tmp && tmp->_x != key)
  {
    if(tmp->_x > key)
      tmp = tmp->_left;
    else
      tmp = tmp->_right;
  }

  return tmp != nullptr;
}

void trh::Treap::erase(int key)
{
  if(!contains(key))
    return;

  Node *less, *greated, *equals;
  split(_root, key, less, greated);
  split(greated, key + 1, equals, greated);
  deleteBranch(equals);
  _root = merge(less, greated);

}

trh::Treap::~Treap()
{
  deleteBranch(_root);
}
