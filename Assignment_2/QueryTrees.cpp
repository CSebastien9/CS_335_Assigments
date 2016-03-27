
/** C.F. Sebastien Dalencourt
 *  CSCI-335 
 *  Professor Stamos
 *  Assignment 2
 *  March 10th, 2016
 */

#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SequenceMap.cpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

template <typename TreeType>
void TestQueryTree(TreeType &a_tree, string &db_filename) {

    ifstream rebasefile(db_filename);
    string db_line;

    if (!rebasefile.is_open()) {   //Program exists if file is not opened or cannot be opened
        exit(EXIT_FAILURE);
    }
    
    while(rebasefile.good()) {
        (getline(rebasefile, db_line));
        
        size_t pos;
        string delimiter = "/";
        string a_reco_seq;
        string an_enz_acro;
        
        //Enzyme acronym is copied into var and deleted from db_line
        pos = db_line.find(delimiter);
        an_enz_acro = db_line.substr(0, pos);
        db_line.erase(0, pos + delimiter.length());
        
        //Copies recognition sequence into var and then deletes it from db_line
        while((pos = db_line.find(delimiter)) != string::npos) {
            a_reco_seq = db_line.substr(0, pos);
            if(a_reco_seq == "") {
                //There are no more sequences in that line
                break;
            } 
            else {
                SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
                a_tree.insert(new_sequence_map);
                db_line.erase(0, pos + delimiter.length());
            }
        }
   }

    string dna;
    cout << "\nEnter DNA Sequence for a Query: ";
    cin >> dna;
    SequenceMap dna_seq(dna);

    if (a_tree.contains(dna_seq)) {
        a_tree.return_node(dna_seq).print_enzymes();
        cout << endl;
    }
    else 
      cout << "\"DNA Sequence NOT FOUND\" -- RETRY OTHER SEQUENCE " << endl;
}

// Sample main for program queryTrees
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  
  string db_filename(argv[1]);
  string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  
  if (param_tree == "BST") {
    
    cout << "I will run the BST code" << endl;
    BinarySearchTree<SequenceMap> bst_tree;
    TestQueryTree(bst_tree, db_filename);
  } 
  else if (param_tree == "AVL") {
    
    cout << "I will run the AVL code" << endl;
    AvlTree<SequenceMap> avl_tree;
    TestQueryTree(avl_tree, db_filename);
  } 
  else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
