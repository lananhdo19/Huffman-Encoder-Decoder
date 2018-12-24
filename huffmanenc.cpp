//Lan Anh Do ld9hu huffmanenc.cpp 11/25/18.
//This uses the heap code from the slides. Thank you!
#include <iostream>
#include <stdlib.h>
#include <map>
#include <stdio.h>
#include "heap.h"
using namespace std;
void findCode(string c, Node* ptr);

int main (int argc, char **argv) {
    // verify the correct number of parameters
    if ( argc != 2 ) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }
 
    FILE *fp = fopen(argv[1], "r");
    // if the file wasn't found, output and error message and exit
    if ( fp == NULL ) {
        cout << "File '" << argv[1] << "' does not exist!" << endl;
        exit(2);
    }

    // read in each character, one by one. 
    binary_heap bh;
    map <char, int> m;        //for char and freq
    map <char, string> coder; //for char and prefix
    char g;
    int symbols = 0;
    while ( (g = fgetc(fp)) != EOF ){
      if (g >= 0x20 && g <= 0x7e){ //gets rid of newline
	m[g] += 1;
       symbols++;
      }
    }

    rewind(fp);

    map<char, int>::iterator i;
    vector<Node*> totalNodes;
    double unique = 0;

    for (i = m.begin(); i!=m.end(); i++){  //put in the char by frequency
      unique++;
      Node * n =  new Node (i -> first, i -> second);
      bh.insert(n);
      totalNodes.push_back(n); //stores all nodes
    }

    while(bh.size() > 1){     //build hoffman tree
      Node * temp = new Node();
      temp -> left = bh.deleteMin();
      temp -> right = bh.deleteMin();
      temp -> freq = temp -> left -> freq + temp -> right -> freq;
      findCode("", temp);    //generate prefix as you create node
      bh.insert(temp);
    }
    
     //print out the prefixes
    cout<<endl;
    for(Node* n: totalNodes){
      if(n->g == 0x20) cout << "space " << n->prefix<<endl;
      else cout << n->g<< " " << n->prefix<<endl;
      coder[n->g] = n->prefix;
    }

    
    cout << "----------------------------------------" << endl;
    double compressedBit = 0;
    while ( (g = fgetc(fp)) != EOF ){
      cout << coder[g]<< " ";      //map serves as encoder
      compressedBit+=coder[g].length();
    }

    cout << "\n----------------------------------------" << endl;
    
    double cost = compressedBit/symbols;
    double uncomp = symbols*8;
    
    cout<<"There are "<<symbols<<" symbols encoded."<<endl;
    cout<<"There are "<< unique << " distinct symbols used."<<endl;
    cout<<"There are "<<uncomp<<" uncompressed bits in original file."<<endl;
    cout<<"There are "<<compressedBit<<" bits in the compressed file." << endl;
    cout<<"The compression ratio is "<< (double)uncomp/compressedBit<<endl;
    cout<<"The cost is "<< cost << " bits per character"<<endl;
    fclose(fp);
}

//finds and stores prefix
void findCode(string c, Node* ptr){
  if (ptr -> right == NULL && ptr -> left ==NULL) ptr -> prefix = c;
  if (ptr -> right != NULL) findCode(c+"1", ptr->right);
  if (ptr -> left != NULL) findCode(c+"0", ptr->left);
}
