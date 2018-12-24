//Lan Anh Do ld9hu heap.h 11/27/18
// Code written by Aaron Bloomfield, 2014
// Released under a CC BY-SA license
// This code is part of the https://github.com/aaronbloomfield/pdr repository

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "node.h"
using namespace std;

class binary_heap {
public:
    binary_heap();
    binary_heap(vector<Node *> vec);
    ~binary_heap();

    void insert(Node *x);
    Node* findMin();
    Node* deleteMin();
    unsigned int size();
    void makeEmpty();
    bool isEmpty();
    void print();

private:
    vector<Node*> heap;
    unsigned int heap_size;

    void percolateUp(int hole);
    void percolateDown(int hole);
};

#endif
