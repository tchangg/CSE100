#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/** // : list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  Authors: Brian Soe, Timothy Chang
 *  Login: bsoe, twc006
 *  Assignment #1
 */


/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }


  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */
  BSTNode<Data>* successor(){
    BSTNode<Data>* tmp = this;
    BSTNode<Data>* p = tmp->parent;

    // if there is no right child
    if(tmp->right == nullptr){
      if(p == nullptr) // when there's no parent
      {
        return nullptr;
      }

      // look for parents as next inorder.
      do
      {
        if(p->left == tmp) // when current node is left child of parent
        {
          break;
        }
        
        // move up of BST
        tmp = p;
        p = p->parent;
        if(p == nullptr) // check if there's no parent again
        {
          return nullptr;
        }
      } while(tmp == p->right);
      return p;
    }

    // search for next inorder from right child
    else    
    {
      tmp = tmp->right;
      while(tmp->left != nullptr) // traverse left descendants of right child
      {
        tmp = tmp->left;
      }
      return tmp;
    }
  }

}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
