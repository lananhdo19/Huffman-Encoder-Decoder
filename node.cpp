//Lan Anh Do ld9hu node.cpp 11/27/2018
#include "node.h"
#include <iostream>
using namespace std;

Node:: Node()
{
    g = '@';
    freq = 1000000;
    left = NULL;
    right = NULL;
    prefix = "";
  }

Node::Node(char c, int f)
{
    g = c;
    freq = f;
    left = NULL;
    right = NULL;
    prefix = "";
  }
void Node::printInfix(Node* ptr) const {
  if (ptr -> left != NULL){
    cout << "(";
    printInfix(ptr -> left) ;
  }

  cout << ptr -> g;


  if (ptr -> right != NULL) {
    printInfix(ptr -> right) ;
    cout << ")";
  }
}



