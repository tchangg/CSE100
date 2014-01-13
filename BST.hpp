#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair
#include <iostream>

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  Authors: Brian Soe, Timothy Chang
 *  Login: bsoe,
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
   */ // TODO
  virtual ~BST() {
    clear();
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ // TODO
  virtual std::pair<iterator,bool> insert(const Data& item) {
    BSTNode<Data>* tmp = root;
    BSTNode<Data>* toAdd = new BSTNode<Data>(item);
    bool second = 0; 
    // when tree is empty 
    if(tmp == nullptr)
    {
      root = toAdd;
      iterator first = BST<Data>::iterator(root);
      isize++;
      second = 1;
      return std::pair<iterator,bool>(first,second);
    }

    // when at least one node exists
    while(tmp->left != nullptr || tmp->right != nullptr)
    {
      if(tmp->data == toAdd->data || tmp->left == nullptr || tmp->right == nullptr)
      {
        break;
      }
      else if(tmp->data > toAdd->data)
      {
        tmp = tmp->left;
      }
      else if(tmp->data < toAdd->data)
      {
        tmp = tmp->right;
      }
    }
    if(tmp->data > toAdd->data)
    {
      tmp->left = toAdd;
      toAdd->parent = tmp;
      second = 1;
    }
    else if(tmp->data < toAdd->data)
    {
      tmp->right = toAdd;
      toAdd->parent = tmp;
      second = 1;
    }
    iterator first = BST<Data>::iterator(toAdd);
    isize++;
    return std::pair<iterator,bool>(first,second);
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ // TODO
  iterator find(const Data& item) const {
     iterator i = typename BST<Data>::iterator(root);
     //cout << item << endl;
     while(*i != item)
     {
       if(*i > item && i.curr->left != nullptr)
       {
         i.curr = i.curr->left;
       }
       else if(*i < item && i.curr->right != nullptr)
       {
         i.curr = i.curr->right;
       }
       else if(*i != item)
       {
         return end();
       }
     }
     return i;
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ // TODO
  void clear() {
    remove(root);
    isize = 0;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    return isize == 0;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ // TODO
  iterator begin() const {
    BSTNode<Data>* tmp = root;
    while(tmp != nullptr && tmp->left != nullptr)
    {
      tmp = tmp->left;
    }
    return typename BST<Data>::iterator(tmp);
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

  private:
   
  void remove(BSTNode<Data>* node)
  {
    if(node != nullptr)
    {
      if(node->left != nullptr)
      {
        remove(node->left);
      }
      if(node->right != nullptr)
      {
        remove(node->right);
      }
      delete node;
      isize--;
    }
  }

 };


#endif //BST_HPP
