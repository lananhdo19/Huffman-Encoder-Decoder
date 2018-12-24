//Lan Anh Do ld9hu huffmandec.cpp
// This program is the skeleton code for the lab 10 in-lab.  It uses
// C++ streams for the file input, and just prints out the data when
// read in from the file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include "node.h"
using namespace std;

int index = 0;
Node * tree = new Node();
void decode(Node* curr, string s);
Node* build(string c, map<string,char> m, Node* ptr);
void buildTree(string c, map<string,char> m, Node* ptr, string allbits);
// main(): we want to use parameters
int main (int argc, char **argv) {
    // verify the correct number of parameters
    if ( argc != 2 ) {
        cout << "Must supply the input file name as the only parameter" << endl;
        exit(1);
    }
    // attempt to open the supplied file; must be opened in binary
    // mode, as otherwise whitespace is discarded
    ifstream file(argv[1], ifstream::binary);
    // report any problems opening the file and then exit
    if ( !file.is_open() ) {
        cout << "Unable to open file '" << argv[1] << "'." << endl;
        exit(2);
    }
    // read in the first section of the file: the prefix codes
   
     map <string, char> m;
   
    while ( true ) {
        string character, prefix;
        // read in the first token on the line
        file >> character;
        // did we hit the separator?
        if ( (character[0] == '-') && (character.length() > 1) )
            break;
        // check for space
        if ( character == "space" )
            character = " ";
        // read in the prefix code
        file >> prefix;
	//make nodes with character and prefix
     
	m[prefix] = character[0];
    }
    
    // read in the second section of the file: the encoded message
    stringstream sstm;
    while ( true ) {
        string bits;
        // read in the next set of 1's and 0's
        file >> bits;
        // check for the separator
        if ( bits[0] == '-' )
            break;
        // add it to the stringstream
        sstm << bits /*+ " "*/;
    }
    string allbits = sstm.str();
    // at this point, all the bits are in the 'allbits' string
    //cout << "All the bits: " << allbits << endl;
    // close the file before exiting
    //----------------------------------------------------------------------//
   
    buildTree("", m, tree, allbits);
    //tree -> printInfix(tree);
    decode(tree, allbits);
    cout<<endl;
    file.close();
}

void decode(Node* curr, string s){
  char c = s[index];
    
  if (s.length()>0){
    if(curr-> left == NULL && curr->right==NULL) {
      cout<<curr->g;
      curr = tree;
      s = s.substr(index);
      index = 0;
      
      decode(curr,s);
    }
 
    else if (c=='1') {
      index++;
      curr = curr -> right;
      decode(curr, s);
    }
    else  {
      index++; 
      curr = curr -> left;
      decode(curr, s);
    }
  }
}
void buildTree(string c, map<string,char> m, Node* ptr, string allbits){

  if(allbits.length()>=0){
    if (m[c]){
      ptr -> prefix = c;
      ptr -> g = m[c];
      if (allbits.length()==0) return;
      c="";
      ptr = tree;
      buildTree(c,m,ptr,allbits);
    }
    else{
      char bit = allbits[0];
      allbits = allbits.substr(1);
      Node* temp = new Node();

      if (bit == '1'){
	if(ptr -> right ==NULL) ptr -> right = temp;
	ptr = ptr -> right;
	buildTree(c+"1",m,ptr,allbits);
      }
      else{
	if(ptr -> left ==NULL) ptr -> left = temp;
	ptr = ptr -> left;
       	buildTree(c+"0",m,ptr,allbits);
      }
    }
  }
}
