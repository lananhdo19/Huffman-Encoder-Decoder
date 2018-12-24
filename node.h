#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
using namespace std;

class Node{
public:
  Node();
  Node(char c, int f);
  void printInfix(Node* ptr) const;
  string findCode(string c, Node* ptr);
  int freq;
  char g;
  string prefix;
  Node * left;
  Node * right;
};
#endif
