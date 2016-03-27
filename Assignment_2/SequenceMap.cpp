
/** C.F. Sebastien Dalencourt
 *  CSCI-335 
 *  Professor Stamos
 *  Assignment 2
 *  March 10th, 2016
 */

#include <iostream>
#include "SequenceMap.h"
using namespace std;

SequenceMap::SequenceMap(const string& dna) {

	recognition_sequence_ = dna;
}

SequenceMap::SequenceMap(const string &a_rec_seq, const string &an_enz_acro) 
	: recognition_sequence_(), enzyme_acronyms_() {
    
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
}

bool SequenceMap::operator<(const SequenceMap &rhs) const {
    
    return recognition_sequence_ < rhs.recognition_sequence_;
}

ostream& operator<<(ostream& os, const SequenceMap& rhs) {
    
    os << "SEQ: " << rhs.recognition_sequence_ << "\t\t";
    
    size_t vec_size = rhs.enzyme_acronyms_.size();
    cout << "ENZ: ";
    for(size_t i = 0; i < vec_size; ++i) {

        os << rhs.enzyme_acronyms_[i] << " ";
    }
    return os;
}
 
void SequenceMap::Merge(const SequenceMap &other_sequence) {
    bool result = false;
    size_t vec_size = enzyme_acronyms_.size();
    
    for(size_t i = 0; i < vec_size; ++i) {
        if(enzyme_acronyms_[i] == other_sequence.enzyme_acronyms_[0]) {
            result = true;
            break;
        }
    }
    
    if(result == false)  
        enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[0]);
}

void SequenceMap::print_enzymes() const {

    size_t vec_size = enzyme_acronyms_.size();
    
    for(size_t i = 0; i < vec_size; ++i) {
        cout << enzyme_acronyms_[i] << "  ";
    }
}


