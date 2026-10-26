#ifndef BST_MULTIMAP
#define BST_MULTIMAP

#include "BSTNode.hpp"
#include "BSTForwardIterator.hpp"
#include "LinkedList.hpp"

#include <queue>

using namespace std;

template <class key_t, class val_t>
class BSTMultimap
{
  protected:
   BSTNode<key_t, val_t>* root;
   BSTNode<key_t, val_t>* sentinel;
   int numItems;

   virtual void insertNode(BSTNode<key_t, val_t>* node);

  public:
   //Creates an empty binary tree
   BSTMultimap();
   virtual ~BSTMultimap();

   //Inserts (key, value) into the multimap
   virtual void insert(const key_t& key, const val_t& value);

   //Removes the key/value pair pointed to by pos
   //(if pos is off the end, does nothing)
   //Returns an iterator pointing to the next node after the
   //deleted node
   virtual BSTForwardIterator<key_t, val_t> remove(const BSTForwardIterator<key_t, val_t>& pos);

   //Removes all items in the tree
   virtual void clear();

   //Returns true if there is an item with "key" as its key
   virtual bool contains(const key_t& key) const;

   //Find the "first" node associated with this key
   //Returns an iterator pointing to that node
   virtual BSTForwardIterator<key_t, val_t> findFirst(const key_t& key) const;
   //Find the "last" node associated with this key
   //Returns an iterator pointing to that node
   virtual BSTForwardIterator<key_t, val_t> findLast(const key_t& key) const;

   //Returns an iterator to the element with the smallest key
   virtual BSTForwardIterator<key_t, val_t> getMin() const;
   //Returns an iterator to the element with the largest key
   virtual BSTForwardIterator<key_t, val_t> getMax() const;

   virtual int getSize() const;
   virtual bool isEmpty() const;
};

#include "BSTMultimap.tpp"

#endif

