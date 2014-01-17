#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

/* Additional */
#include <limits.h>

using namespace std;

/** List real name(s) and login name(s) 
 *  of the author(s) of this assignment
 *  Authors: Brian Soe, Timothy Chang
 *  Login: bsoe, twc006
 *  Assignment #1
 */

int testDriver()
{
  cout << "\n========== USING OTHER TESTER ==========\n" << endl;

  /* Set-up */
  srand(time(NULL)); // reset random generator
  vector<int> list;
  BST<int> tree;
  int N = rand()%2; // determine if the number will be negative or not.
  if(N == 0)
  {
    N = -1;
  }
  unsigned int traverse_counter = 0;

  list.push_back(0); // adding corner and basic cases
  list.push_back(1);
  list.push_back(-1);
  list.push_back(INT_MIN);
  list.push_back(INT_MAX);
  list.push_back((N+2)*(rand()%100+2)); // value that could be +/-
  list.push_back(rand()%100+2); // value always positive
  /*for(int i = 200; i < 300; i++)
  {
    list.push_back(i);
  }*/

  vector<int>::iterator beginV = list.begin();
  vector<int>::iterator endV = list.end();

  cout << "Given vector is: [";
  while(beginV != endV)
  {
    cout << *beginV;
    beginV++;
    if(beginV != endV)
    {
      cout << ", ";
    }
  }
  cout << "]" << endl;
  
  // Testing size() on an empty binary tree 
  cout << "Testing size() when empty ... ";
  if(tree.size() == 0)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  } 
  
  // Testing empty() on an empty binary tree
  cout << "Testing empty() when empty ... ";
  if(tree.empty() == true)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  // Testing clear() on an empty binary tree
  cout << "Testing clear() when empty ... ";
  tree.clear();
  if(tree.size() == 0 && tree.empty())
  {
    std::pair<BST<int>::iterator,bool> pair = tree.insert(0);

    // if second element of pair is true, then insert successful
    if(pair.second) 
    {
      cout << "PASSED!" << endl;
      tree.clear();
    }
  }
  else
  {
    cout << "FAILED" << endl;
  }
  
  // Testing insert() and begin() on empty binary tree
  cout << "Testing insert() and begin() when initially empty ... ";

  tree.insert(*(list.begin()));
  // if tree's first element is same as sorted list's first element
  if(*(tree.begin()) == *(list.begin()))
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }
  
  // Testing insert() for inserting duplicate data
  cout << "Testing insert() when inserting repeated data ... ";
  std::pair<BST<int>::iterator,bool> pair = tree.insert(*(list.begin()));
  if(!pair.second && tree.size() == 1) // it should not added to tree
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }
  
  // Testing empty() on a binary tree with at least one data
  cout << "Testing empty() with at least one data ... ";
  if(tree.empty() == false)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  // Testing clear() on a nonempty binary tree
  cout << "Testing clear() when there's an data ... ";
  tree.clear();
  if(tree.size() == 0)
  {
    if(tree.insert(rand()%100).second)
    {
      cout << "PASSED!" << endl;
      tree.clear();
    }
  }
  else
  {
    cout << "FAILED" << endl;
  }
  
  // Testing insert() by inserting all the data in vector
  cout << "Testing insert() with all data of vector ... ";
  beginV = list.begin();
  while(beginV != endV)
  {
    pair = tree.insert(*beginV);

    // when iterator is invalid or repeated value, fail
    if(*(pair.first) != *beginV || !pair.second)
    {
      cout << "FAILED" << endl;
      break;
    }
    beginV++;
    if(beginV == endV)
    {
      cout << "PASSED!" << endl;
    }
  }
 
  // Testing size() after inserting all data in vector
  cout << "Testing size() with all data of vector ... ";
  if(tree.size() == list.size())
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  // Testing begin() on binary tree
  cout << "Testing begin() ... ";
  sort(list.begin(),list.end());
  beginV = list.begin();
  BST<int>::iterator beginT = tree.begin(); //call begin()
  while(beginT != tree.end())
  {
    if(*(beginT) != *(beginV)) // when tree value != list value
    {
      cout << "FAILED" << endl;
      break;
    }
    beginT++;
    beginV++;
    if(beginT == tree.end()) // pass if it went through entire tree
    {
      cout << "PASSED!" << endl;
    }
  }
   
  // Testing by traversing BST in-order
  cout << "\nTraversing BST (in-order): " << endl;
  beginT = tree.begin();
  beginV = list.begin();
  while(beginT != tree.end())
  {
    cout << "  * " << *beginT << " --> ";
    if(*beginT == *beginV)
    {
      cout << "Correct." << endl;
      traverse_counter++;
    }
    else
    {
      cout << "Incorrect. The correct value is " << *beginV << "." << endl; 
    }
    beginT++;
    beginV++;
  }
  cout << "Traversal Result: ";
  if(traverse_counter == list.size()) // if it traversed all elements
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  /** Testing successor() method using pre-order increment because it
   * calls successor()
   */
  cout << "\nTesting successor() with pre-order increment ... " << endl;
  beginT = tree.begin(); //start at beginning of tree
  beginV = list.begin(); //start at beginning of vector
  traverse_counter = 0;
  for(unsigned int i = 1; i < tree.size(); i++)
  {
    cout << *(++beginT) << " is successor of " << *beginT; 
    if(*beginT == *(++beginV)) //check values after pre-increment BST
    {
      cout << " --> Correct." << endl;
      traverse_counter++;
    }
    else
    {
      cout << " --> Incorrect. Correct value is " << *beginV << endl;
    }
  }
  if(traverse_counter == tree.size()-1)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  cout << "\n========== FINISHED TESTING ==========\n" << endl;
  return 0;
}
/**
 * A simple test driver for the BST class template.
 * P1 CSE 100 2013
 * Author: P. Kube (c) 2013
 */
int main() {

  /* Create an STL vector of some ints */
  vector<int> v;
  v.push_back(3);
  v.push_back(4);
  v.push_back(1);
  v.push_back(100);
  v.push_back(-33);

  /* Create an instance of BST holding int */
  BST<int> b;

  /* Insert a few data items. */
  vector<int>::iterator vit = v.begin();
  vector<int>::iterator ven = v.end();
  for(; vit != ven; ++vit) {
    // all these inserts are unique, so should return a std::pair
    // with second part true
    std::pair<BST<int>::iterator,bool> pr = b.insert(*vit);
    if(! pr.second ) {
      cout << "Incorrect bool return value when inserting " << *vit << endl;
      return -1;
    }
    if(*(pr.first) != *vit) {
      cout << "Incorrect iterator return value when inserting " << *vit << endl;
      return -1;
    }  
  }

  /* Test size. */
  cout << "Size is: " << b.size() << endl;
  if(b.size() != v.size()) {
    cout << "... which is incorrect." << endl;
    return -1;
  }

  /* Test find return value. */
  vit = v.begin();
  for(; vit != ven; ++vit) {
    if(*(b.find(*vit)) != *vit) {
      cout << "Incorrect return value when finding " << *vit << endl;
      return -1;
    }
  }
  
  /* Sort the vector, to compare with inorder iteration on the BST */
  sort(v.begin(),v.end());

  /* Test BST iterator; should iterate inorder */
  cout << "traversal using iterator:" << endl;
  vit = v.begin();
  BST<int>::iterator en = b.end();
  BST<int>::iterator it = b.begin();
  for(; vit != ven; ++vit) {
    if(! (it != en) ) {
      cout << *it << "," << *vit << ": Early termination of BST iteration." << endl;
      return -1;
    }
    cout << *it << endl;
    if(*it != *vit) {
      cout << *it << "," << *vit << ": Incorrect inorder iteration of BST." << endl;
      return -1;
    }
    ++it;
  }
  cout << "OK." << endl;
  b.clear();
  testDriver();
}
