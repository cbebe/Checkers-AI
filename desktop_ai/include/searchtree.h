#ifndef _SEARCHTREE_H_
#define _SEARCHTREE_H_

/* 
  Search Tree Implementation 
  pls help
*/

#include <vector>
#include <list>

template <typename T>
class Node {
public:


private:
  Node<T>* parent;
  std::list<Node<T>*> children;  
};

template <typename T>
class SearchTree {
public:


private:
  Node<T> root;
};

#endif