
/** C.F. Sebastien Dalencourt
 *  CSCI-335 
 *  Professor Stamos
 *  Assignment 2
 *  March 10th, 2016
 */

#include <iostream>
#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.cpp"
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

template <typename TreeType>
void TestTrees(TreeType &a_tree, string &db_filename, string &query_filename) {

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

    double num_nodes = a_tree.num_of_nodes();
    cout << "NUMBER OF NODES IN TREE: " << num_nodes << endl;
    double ipl = a_tree.get_ipl_num();
    cout << "INTERNAL PATH LENGTH: " << ipl << endl;
    double avg_depth = ipl/num_nodes;
    cout << "AVERAGE DEPTH OF TREE: " << avg_depth << endl;
    double log_nodes = log2(a_tree.num_of_nodes());
    cout << "RATIO OF AVERAGE DEPTH: " << avg_depth/log_nodes << endl;

    size_t successful_queries = 0, rec_call_count = 0, count = 0;
    
    ifstream sequence_file(query_filename);
    string seq_line;

    if (!sequence_file.is_open()) {   //Program exists if file is not opened or cannot be opened
        exit(EXIT_FAILURE);
    }

    while(sequence_file.good()) {
        (getline(sequence_file, seq_line));
        SequenceMap new_seq_obj(seq_line);
        rec_call_count += a_tree.total_recursion_num(new_seq_obj, count);

        if(a_tree.contains(new_seq_obj))
          ++successful_queries;
    }

    double num_queries = successful_queries;
    cout << "\nTOTAL NUMBER OF SUCCESSFUL QUERIES: " << num_queries << endl;
    double rec_calls = rec_call_count;
    cout << "TOTAL NUMBER OF RECURSION CALLS: " << rec_calls << endl;
    cout << "AVERAGE NUMBER OF RECURSION CALLS: " << rec_calls/num_queries << endl;

    //Removing every other sequence
    ifstream file(query_filename);
    seq_line.clear();
    size_t line_counter = 0, del_rec_call_count = 0, del_count = 0, removals = 0;

    while(file.good()) {
        (getline(file, seq_line));
        
        if(line_counter % 2 == 0) {
          ++removals;
          SequenceMap new_seq_obj(seq_line);
          a_tree.remove(new_seq_obj);
          del_rec_call_count += a_tree.total_del_rec_num(new_seq_obj, del_count);
        }
        ++line_counter;
    }

    double num_removals = removals;
    cout << "\nTOTAL NUMBER OF SUCCESSFUL REMOVES: " << num_removals << endl;
    double del_call_removals = del_rec_call_count;
    cout << "TOTAL RECURSION CALL FOR REMOVAL: " << del_call_removals << endl;
    cout << "AVERAGE NUMBER OF RECURSION CALLS FOR REMOVAL: " << del_call_removals / num_removals << endl;

    cout << "\nRE-COMPUTING STATISTICS" << endl;
    double new_num_nodes = a_tree.num_of_nodes();
    cout << "NUMBER OF NODES IN TREE: " << new_num_nodes << endl;
    double new_ipl = a_tree.get_ipl_num();
    cout << "INTERNAL PATH LENGTH: " << new_ipl << endl;
    avg_depth = new_ipl /new_num_nodes;
    cout << "AVERAGE DEPTH OF TREE: " << avg_depth << endl;
    log_nodes = log2(a_tree.num_of_nodes());
    cout << "RATIO OF AVERAGE DEPTH: " << avg_depth/log_nodes << endl;
    cout << endl;
}

int main(int argc, char **argv) {
  
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }

  string db_filename(argv[1]);
  string query_filename(argv[2]);
  string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and query file is " << query_filename << endl;
  
  if (param_tree == "BST") {
    cout << "I will run the BST code \n" << endl;
    BinarySearchTree<SequenceMap> bst_tree;
    TestTrees(bst_tree, db_filename, query_filename);
  } 
  else if (param_tree == "AVL") {
    cout << "I will run the AVL code \n" << endl;
    AvlTree<SequenceMap> avl_tree;
    TestTrees(avl_tree, db_filename, query_filename);
  } 
  else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}




