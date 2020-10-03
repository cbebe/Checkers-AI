// ---------------------------------------------------
// Name : Charles Ancheta
// ID: 1581672
// CMPUT 275 , Winter 2020
//
// Weekly Exercise 4: Dynamic Hashing
// ---------------------------------------------------

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "linked_list.h"
#include <cassert>

/*
  A hash table for storing items. It is assumed the type T of the item
  being stored has a hash method, eg. you can call item.hash(), which
  returns an unsigned integer.

  Also assumes the != operator is implemented for the item being stored,
  so we could check if two items are different.

  If you just want store integers int for the key, wrap it up in a struct
  with a .hash() method and both == and != operator.
*/

template <typename T>
class HashTable {
public:
  // creates an empty hash table with the given number of buckets.
  HashTable(unsigned int tableSize = 10); // default size is 10
  ~HashTable();

  // Check if the item already appears in the table.
  bool contains(const T& item) const;
  // Insert the item, do nothing if it is already in the table.
  // Returns true iff the insertion was successful (i.e. the item was not there).
  bool insert(const T& item);
  // Removes the item after checking, via assert, that the item was in the table.
  void remove(const T& item);
  unsigned int size() const;

private:
  LinkedList<T> *table; // start of the array of linked lists (buckets)
  unsigned int numItems; // # of items in the table
  unsigned int tableSize; // # of buckets

  // Computes the hash table bucket that the item maps into
  // by calling its .hash() method.
  unsigned int getBucket(const T& item) const;
  void changeSize(bool toShrink); // shrinks or expands table
  void copy(LinkedList<T> *newTable, unsigned int size); // copies contents to a new table
};

template <typename T>
HashTable<T>::HashTable(unsigned int tableSize) {
  assert(((void)"Number of buckets must be at least 1", tableSize > 0)); // make sure there is at least one bucket

  // calls the constructor for each linked list
  // so each is initialized properly as an empty list
  table = new LinkedList<T>[tableSize];

  numItems = 0; // we are not storing anything
  this->tableSize = tableSize;
}

template <typename T>
HashTable<T>::~HashTable() {
  // this will call the destructor for each linked
  // list before actually deleting this table from
  // the heap
  delete[] table;
}

template <typename T>
bool HashTable<T>::contains(const T& item) const {
  unsigned int bucket = getBucket(item);
  return table[bucket].find(item) != NULL;
}


template <typename T>
bool HashTable<T>::insert(const T& item) {
  // if the item is here, return false
  if (contains(item)) {
    return false;
  }
  else {
    // otherwise, insert it into the front of the list
    // in this bucket and return true
    unsigned int bucket = getBucket(item);
    table[bucket].insertFront(item);
    ++numItems;

    if (numItems > tableSize) {
      changeSize(false); // expands table
    } else if (numItems < tableSize/4 && tableSize > 10) {
      changeSize(true); // shrinks table
    }
    return true;
  }
}

template <typename T>
void HashTable<T>::remove(const T& item) {
  unsigned int bucket = getBucket(item);

  ListNode<T>* link = table[bucket].find(item);

  // make sure the item was in the list
  assert(link != NULL);

  table[bucket].removeNode(link);

  --numItems;
  if (numItems < tableSize/4 && tableSize > 10) {
    changeSize(true); // shrinks table
  }
}

template <typename T>
unsigned int HashTable<T>::size() const {
  return numItems;
}


template <typename T>
unsigned int HashTable<T>::getBucket(const T& item) const {
  return item.hash() % tableSize;
}

// copies the contents of the old table to a new table
template <typename T>
void HashTable<T>::copy(LinkedList<T> *newTable, unsigned int size) {
  T num; ListNode<T> *it; unsigned int bucket; // declare variables
  for (unsigned int i = 0; i < tableSize; i++) {
    while (table[i].getFirst() != NULL) {
      it = table[i].getFirst();
      num.val = ((*it).item).hash(); // wraps value in UIntWrapper
      bucket = num.val % size; // determines where to insert the value
      newTable[bucket].insertFront(num);
      table[i].removeFront();
    }
  }
}

// changes table size when conditions are met
template <typename T>
void HashTable<T>::changeSize(bool toShrink) {

  // determining new table size
  unsigned int newTableSize;
  if (toShrink) {
    // max(tableSize/2, 10)
    if (tableSize > 10) {
      newTableSize = tableSize / 2;
    } else {
      newTableSize = 10;
    }
  } else { 
    newTableSize = tableSize * 2; // expands the table
  }

  LinkedList<T> *temp = table; // point to old table
  LinkedList<T> *newTable = new LinkedList<T>[newTableSize];
  copy(newTable, newTableSize);
  
  table = newTable; // points table to new table
  delete[] temp; // deletes old table
  tableSize = newTableSize;
}

#endif
