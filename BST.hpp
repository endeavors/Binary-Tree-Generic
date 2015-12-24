/*******************************************************************/
/* Name: Gurkirat Singh
 * Description: This program is an implementation of the binary search
 *                 tree. It includes the find, clear, and insert methods
 *                 that follow the binary search tree principles. An
 *                 iterator is used to help keep track of the nodes
 *                 and a separate size variable is used to keep track of 
 *                 the size of the tree.
 *******************************************************************/

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

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
      Initialize an empty BST with root null pointer and size of 0
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ 
  virtual ~BST() {
    //call clear to delete all nodes; set size =0; and set root to null
    clear();   
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ 
  virtual std::pair<iterator,bool> insert(const Data& item) {
    
    //initialize an iterator node
    BSTNode<Data> *currNode = root;
    
    //BST size is 0, so create a pair with the root and bool True to indicate
    //successful insertion
    if (root == nullptr){
        root = new BSTNode<Data>(item);
        isize++;    
        return std::make_pair(typename BST<Data>::iterator(root), true);
    }else{
        
        //keep iterating until we have found either a duplicate value or a 
        //null pointer where we can insert the node
        while (currNode->data != item){

            //go to the left since data is less than the current node
            if (item < currNode->data){

                //we have found the location to insert
                if (currNode->left == nullptr){
                    BSTNode<Data>* nodeToInsert = new BSTNode<Data>(item);
                    currNode->left = nodeToInsert;
                    nodeToInsert->parent = currNode;
                    isize++;
                    //iterator points to the inserted node
                    return std::make_pair(typename BST<Data>::iterator\
                        (nodeToInsert), true);
                }else{
                    //keep going left of the node
                    currNode = currNode->left;
                }
            }else{
                //data is greater than the current node, so go right
                if(currNode->right == nullptr){
                    BSTNode<Data>* nodeToInsert = new BSTNode<Data>(item);
                    currNode->right = nodeToInsert;
                    nodeToInsert->parent = currNode;
                    isize++;
                    //successful insert to the right of the parent of current
                    //node
                    return std::make_pair(typename BST<Data>::iterator\
                        (nodeToInsert),true);
                    
                }else{
                    //keep going right
                    currNode = currNode->right;
                }
            }
        }
    }
    
    //possible duplicate insertion 
    return std::make_pair(typename BST<Data>::iterator(currNode), false);
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ 
  iterator find(const Data& item) const {
    if (root == nullptr){
        //return nullptr since there're no nodes in the BST
        return end();
    }
      
    //declare and initialize a starting iterator node
    BSTNode<Data>*currNode = root;
      
    //don't stop until we either don't find the node in the entire tree
    //or the node is not where it is supposed to be
    while (currNode->data != item && currNode != nullptr){

        //go left
        if (item < currNode->data){
            //return nullptr iterator since node is not there
            if (currNode->left == nullptr){
                return end();
            }else{
                currNode = currNode->left;
            }
        }else{
              
            //item to find is greater than the current node
            if (currNode->right == nullptr){
                return end();
            }else{
                currNode = currNode->right;
            }
        }
    }
    
    //we found the node; return it in form of an iterator  
    return typename BST<Data>::iterator(currNode);
  }

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ 
  void clear() {
    clearBSTRecursively(root);
    root = nullptr;    
    isize = 0;
  }

  /** Return true if the BST is empty, else false.
   */ 
  bool empty() const {
    if (isize == 0){
        return true;
    }
    return false;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ 
  iterator begin() const {

    //start from root and keept going to the left to find
    //the lowest value in the tree until hit null pointer
    BSTNode<Data> *iteratorNode = root;
    if (iteratorNode !=  nullptr){
        while (iteratorNode->left != nullptr){
            iteratorNode = iteratorNode->left;
        }
    }
      
    return typename BST<Data>::iterator(iteratorNode);
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

private:
    void clearBSTRecursively(BSTNode<Data>*node){

        //delete every node post-order traversal
        //So go left, and then right, and then visit the node
        if (node != nullptr){
            //keep going left until hit null pointer
            clearBSTRecursively(node->left);
            clearBSTRecursively(node->right);
            //now delete the node and set it to nullptr
            delete node;
            node = nullptr;
        }
    }

 };


#endif //BST_HPP
