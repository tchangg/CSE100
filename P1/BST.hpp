#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair
#include <iostream>

/** // : list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  Authors: Brian Soe, Timothy Chang
 *  Login: bsoe, twc006
 *  Assignment #1
 */
using namespace std;
template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */  
  virtual ~BST() {
    //don't call clear if binary tree is already empty
    if(root != nullptr) 
    {
      clear();
    }
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ //  
  virtual std::pair<iterator,bool> insert(const Data& item) {
    BSTNode<Data>* tmp = root;
    BSTNode<Data>* toAdd;
    bool second = 0;
 
    // when tree is empty 
    if(tmp == nullptr)
    {
      root = new BSTNode<Data>(item); // allow root to be new node
      iterator first = BST<Data>::iterator(root); // iterator pointing to root
      second = 1; // true, it has been added
      isize++; // increase size
      return std::pair<iterator,bool>(first,second);
    }

    // when at least one node exists
    while(tmp->left != nullptr || tmp->right != nullptr)
    {
      if(tmp->data > item && tmp->left != nullptr)
      {
        tmp = tmp->left; // follow path to left child
      }
      else if(tmp->data < item && tmp->right != nullptr)
      {
        tmp = tmp->right; // follow path to right child
      }
      else
      {
        break;
      }
    }

    // adding node
    if(tmp->data > item) 
    {
      tmp->left = new BSTNode<Data>(item); // link left child with new node
      toAdd = tmp->left;
      tmp->left->parent = tmp; // link current node as parent of new node
      second = 1; // successfully added
    }
    else if(tmp->data < item)
    {
      tmp->right = new BSTNode<Data>(item); // link left child with new node
      toAdd = tmp->right;
      tmp->right->parent = tmp; // link current node as parent of new node
      second = 1; // successfully added
    }

    iterator first = BST<Data>::iterator(toAdd); //iterator pointing to new node
    if(second == 1)
    {
      isize++; // only increase size when it's actually added
    }
    return std::pair<iterator,bool>(first,second);
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */
  iterator find(const Data& item) const {
     // use this iterator to search through tree
     iterator i = typename BST<Data>::iterator(root);
     while(*i != item) // operator* of BSTIterator
     {
       // if current node in iterator is greater than item
       // and it has a left child
       if(*i > item && i.curr->left != nullptr) 
       {
         i.curr = i.curr->left; // move to left child
       }
       // if current current node in iterator is
       // less than item and it has a right child
       else if(*i < item && i.curr->right != nullptr)
       {
         i.curr = i.curr->right; // move to right child
       }
       //if above cases not true and current node's key
       //not equal to item, return end iterator
       else if(*i != item)
       {
         return end(); // use iterator poiting to null
       }
     }
     return i; // return changed iterator
  }

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const {
    return isize; 
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ //  
  void clear() {
    // only clear if binary tree is not empty
    if(root != nullptr)
    {
      remove(root->left); // recursively call to remove left descendants
      remove(root->right); // recursively call to remove right descendants

      // remove/delete root separately
      delete root;
      root = nullptr;
      isize--;
    }
  }

  /** Return true if the BST is empty, else false.
   */ //  
  bool empty() const {
    return root == nullptr && isize == 0;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ //  
  iterator begin() const {
    BSTNode<Data>* tmp = root;
    while(tmp != nullptr && tmp->left != nullptr)
    {
      tmp = tmp->left;
    }
    return typename BST<Data>::iterator(tmp); // return left-most child
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }
  
  /**
   * Private helper method remove() called by clear(). It removes all
   * children nodes of the node that is passed in, and then removes
   * the node that is passsed in to the argument. It recursively
   * clears the children in the left and right subtrees of the
   * node if the children exist.
   */  
  private: void remove(BSTNode<Data>* node) // used for clear()
  {
    if(node != nullptr) //if node is not null
    {
      if(node->left != nullptr) //if left child exists
      {
        remove(node->left); // remove left descendants
      }
      if(node->right != nullptr) //if right child exists
      {
        remove(node->right); // remove right descendants
      }
  
      // handle memory leak
      delete node;
      node = nullptr;
      isize--;
    }
  }
 };


#endif //BST_HPP
