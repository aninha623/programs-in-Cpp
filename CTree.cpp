//includes and usings

#include "CTree.h"
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cstring>

using std::string;
using std::ostream;
using std::endl;

//non default constructor to create new tree
CTree::CTree (char initial) : data(initial), kids(nullptr), sibs(nullptr), prev(nullptr) {}


//^ operator to do the same thing as addChild
CTree& CTree::operator+(CTree& rt){
    this -> addChild(&rt); //call addChild with the address of the root and store in this
    return *this;
} 


// return true if two CTrees match node by node
bool CTree::operator==(const CTree &root){
    //use treeCompare to return self and root provided
    return treeCompare(this, &root); 
}
  
// siblings and children must be unique, return true if added, false otherwise
bool CTree::addChild(char ch){
    CTree *new_child = new CTree(ch); //initialize new CTree with ch as data
    bool success = addChild(new_child);
    if (!success){ //if addChild fails, delete memory that was allocated
        delete new_child;
    }
    return success;
}

// add tree root for better building, root should have null prev and sibs 
// returns false on any type of failure, including invalid root
bool CTree::addChild(CTree *root){
    //if root doesn't exist, cannot add/check validity of root
    if (!root || root -> prev != nullptr || root -> sibs != nullptr){
        return false;
    }
    
    //if parent has no kids
    if (!kids){
        kids = root; //set kid to be the root
        root -> prev = this;
        return true;
    }
    
    //call addSibling to add sibling to the kid
    return kids -> addSibling(root);
}

// all characters, separated by newlines, including at the end
string CTree::toString(){
    std::stringstream ss; //initialize stringstream
    ss << data << std::endl; //store data in stream

    if (kids != NULL){
        ss << kids -> toString(); //if there are any kids, store them recursively
    }
    if (sibs != NULL){
        ss << sibs -> toString(); //if there are any siblings, store them recursively
    }
    return ss.str(); //return stream as a string
}

// add new sibling node with provided char ch data to be stored in the sibling, return true if succeeds
bool CTree::addSibling(char ch){
    CTree *new_sibling = new CTree(ch); //initialize new CTree with ch as data
    bool success = addSibling(new_sibling);
    if (!success){ //if addSibling fails, delete memory that was allocated
        delete new_sibling; 
    }
    return success;
}

// add new sibling node with provided root of other tree data to be stored in the sibling, return true if succeeds in order
bool CTree::addSibling(CTree *root){
    //if root doesn't exist, cannot add/check validity of root
    if (!root || root -> prev != nullptr || root -> sibs != nullptr){
        return false;
    }

    //to prevent segmentation fault
    if (!sibs && !prev){
        return false;
    }

    //check if the sibling already exists, if yes return false
    if (root -> data == data){
        return false;
    }

    //sort through using recursion to see where the root should be added
    if (root -> data < data){ //if the current existing node is greater than the root
        root -> sibs = this; //point root's siblings to be the node
        root -> prev = prev; //point root's previous to the parent
        //if the node's previous kid pointer points to it, it is the first child
        if (prev -> kids == this){
            prev -> kids = root; //set the node's previous (parent)'s child to be the root
        }
        else{ //otherwise, previous will link to some sibling
            prev -> sibs = root; //link previous's siblings to be root
        }
        prev = root; //swap
        return true;
    }
    
    //if the tree you're adding to doesn't have any siblings, just add the root directly to the right
    if (!sibs){
        sibs = root;
        root -> prev = this;
        return true;
    }
    

    //call function recursively to keep checking the tree's sibling's next sibling
    return sibs -> addSibling(root);
}

// compare if two trees are equal to each other
bool CTree::treeCompare(const CTree *a, const CTree *b) const{
    //if both are null they are equal
    if ((a == NULL) && (b == NULL)){
        return true;
    }
    //if only one of them is null they are not equal
    if ((a == NULL) || (b == NULL)){
        return false;
    }
    else if (a -> data != b -> data){
        return false;
    }
    
    //use recursion to check if the kids are the same
    bool kids_same = treeCompare(a -> kids, b -> kids);

    //use recursion to check if the siblings are the same
    bool siblings_same = treeCompare(a -> sibs, b -> sibs);

    //if the kids and the siblings are both true, return true
    bool trees_equal = kids_same && siblings_same;

    return trees_equal;
}

//overload << operator to return the string by calling toString()
std::ostream& operator<<(std::ostream& os, CTree& rt){
    os << rt.toString();
    return os;
}

//destructor to clear all children of current node and all siblings to right of current node
CTree::~CTree() {
    //free all allocated memory recursively
    delete kids;
    delete sibs;
}
