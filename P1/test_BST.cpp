#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

/* Additional */
#include <limits.h>

using namespace std;

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  Authors: Brian Soe, Timothy Chang
 *  Login: bsoe, twc006
 *  Assignment #1
 */

int testDriver()
{
  cout << "\n========== USING OTHER TESTER ==========" << endl;

  /* Set-up */
  srand(time(NULL)); // reset random generator
  vector<int> list;
  BST<int> tree;
  int N = rand()%2; // randomly determine if the number will be negative or not.
  if(N == 0)
  {
    N = -1;
  }
  unsigned int traverse_counter = 0;

  list.push_back(0); // adding corner and basic cases
  list.push_back(1);
  list.push_back(-1);
  //list.push_back(INT_MIN); //removed due to memory leak
  //list.push_back(INT_MAX); //removed due to memory leak
  list.push_back((N+2)*(rand()%100+2)); // value that could be negative or positive
  list.push_back(rand()%100+2); // value always positive

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
  
  cout << "Testing size() when empty ... ";
  if(tree.size() == 0)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  } 

  cout << "Testing empty() when empty ... ";
  if(tree.empty() == true)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  cout << "Testing clear() when empty ... ";
  if(tree.getRoot() == nullptr && tree.size() == 0 && tree.empty())
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  cout << "Testing insert() and begin() when initially empty ... ";
  tree.insert(*(list.begin()));
  if(*(tree.begin()) == *(list.begin()))
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  cout << "Testing insert() when inserting repeated data ... ";
  std::pair<BST<int>::iterator,bool> pair = tree.insert(*(list.begin()));
  if(!pair.second && tree.size() == 1)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  cout << "Testing empty() with at least one data ... ";
  if(tree.empty() == false)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  cout << "Testing clear() when there's an data ... ";
  tree.clear();
  if(tree.size() == 0 && tree.insert(rand()%100).second)
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }
  tree.clear();

  cout << "Testing insert() with all data of vector ... ";
  beginV = list.begin();
  while(beginV != endV)
  {
    pair = tree.insert(*beginV);
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

  cout << "Testing size() with all data of vector ... ";
  if(tree.size() == list.size())
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }

  cout << "Testing begin() ... ";
  sort(list.begin(),list.end());
  beginV = list.begin();
  BST<int>::iterator beginT = tree.begin();
  while(beginT != tree.end())
  {
    if(*(beginT) != *(beginV))
    {
      cout << "FAILED" << endl;
      break;
    }
    beginT++;
    beginV++;
    if(beginT == tree.end())
    {
      cout << "PASSED!" << endl;
    }
  }
 
  cout << "Traversing BST (in-order): " << endl;
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
  cout << "Complete! Traversal Result: ";
  if(traverse_counter == list.size())
  {
    cout << "PASSED!" << endl;
  }
  else
  {
    cout << "FAILED" << endl;
  }
  cout << "========== FINISHED TESTING ==========\n" << endl;
  //TODO call destructor here
  //TODO successor()
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

  testDriver();
}
