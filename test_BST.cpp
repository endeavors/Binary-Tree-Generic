/*********************************************************************
 * Description: Tester program for binary search tree.
 */

#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {

  /* Create an STL vector of some ints */
  vector<int> v;
  v.push_back(3);
  v.push_back(4);
  v.push_back(1);
  v.push_back(100);
  v.push_back(-33);
  v.push_back(58);
  v.push_back(51);
  v.push_back(8);

  
  /* Create an instance of BST holding int */
  BST<int> b;
  
  cout << "EMPTY? -- " << b.empty() << endl;

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

  cout << "Finding non-existing value" << endl;
  BST<int>::iterator exValue = b.find(50);
  if (exValue == b.end()){
    cout << "Value is null" << endl;
  }else{
    cout << "Find 50 " << *(exValue) << endl;
  }

  std::pair<BST<int>::iterator,bool> dupInsert = b.insert(100);
  cout << "DUPLICATE INSERT: Return value -- " << dupInsert.second << endl;
  cout << "DUPLICATE VALUE: " << *(dupInsert.first)  << endl;
  cout << "BST current size: " << b.size() << endl << endl;
  
  /* Find valid value */
  BST<int>::iterator fValue = b.find(8);
  if (fValue == b.end()){
    cout << "Value 8 is null" << endl;
  }else{
    cout << "Found: " << *(fValue) << endl;
  }
  
  cout << "Current Size: " << b.size() << endl;

  /* Test clear*/
  b.clear();
  cout << "BST size: " << b.size() << endl;
  cout << "END" << endl;
 
}
