
/** C.F. Sebastien Dalencourt
 *  CSCI-335 
 *  Professor Stamos
 *  Assignment 2
 *  March 10th, 2016
 */

#include <iostream>
#include <string>
#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.cpp"
#include <cstdlib>
#include <fstream>
using namespace std;

template <typename TreeType>
void TestRangeQuery(TreeType &a_tree, string &db_filename, string &key1, string &key2) {

    SequenceMap lower_bound(key1);
    SequenceMap upper_bound(key2);

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
        
        //Enzyme acronym is copied and deleted from db_line
        pos = db_line.find(delimiter);
        an_enz_acro = db_line.substr(0, pos);
        db_line.erase(0, pos + delimiter.length());
        
        while((pos = db_line.find(delimiter)) != string::npos) {
            a_reco_seq = db_line.substr(0, pos);
            if(a_reco_seq == "") {
                break;
            } 
            else {
                SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
                a_tree.insert(new_sequence_map);
                db_line.erase(0, pos + delimiter.length());
            }
        }
    }
    a_tree.print_range_elem(lower_bound, upper_bound);
} 

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <string> <string2>" << endl;
    return 0;
  }
  string db_filename(argv[1]);
  string str1(argv[2]);
  string str2(argv[3]);
  cout << "Input file is " << db_filename << " ";
  cout << "String 1 is " << str1 << "   and string 2 is " << str2 << endl;

  AvlTree<SequenceMap> avl_tree;
  TestRangeQuery(avl_tree, db_filename, str1, str2);  

  return 0;
}
