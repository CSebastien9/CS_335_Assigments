
/** C.F. Sebastien Dalencourt
 *  CSCI-335 
 *  Professor Stamos
 *  Assignment 2
 *  March 10th, 2016
 */

#ifndef SequenceMap_hpp
#define SequenceMap_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

/** Brief explanation of the SequenceMap class:
 */
class SequenceMap {

private:
    string recognition_sequence_ ;
    vector<string> enzyme_acronyms_;
    
public:
    //Default "Big five"
    SequenceMap() = default;
    SequenceMap(const SequenceMap &rhs) = default;
    SequenceMap& operator=(const SequenceMap &rhs) = default;
    SequenceMap(SequenceMap &&rhs) = default;
    SequenceMap& operator=(SequenceMap &&rhs) = default;
    ~SequenceMap() = default;

    /** Parameterized Constructor
     *  Constructs a SequenceMap object with one given dna sequence
     *  @post new SequenceMap object is created containing sequence
     */
    SequenceMap(const string& dna);

    /** Parameterized Constructor
     *  Constructs a SequenceMap object with the two given strings
     *  @post new SequenceMap object is created containing passed params
     */
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro);
    
    /** Comparison operator
     *  Compares recognition sequence strings based on the string comparison
     *  @post recognition sequence strings are distinguished from one another
     *   based on which one is smaller or greater
     */
    bool operator<(const SequenceMap &rhs) const;
    
    /** Ouptput stream operator<<
     *  Prints content of SequenceMap object
     *  @post SequenceMap object's content can now be printed
     */
    friend ostream& operator<<(ostream& os, const SequenceMap& rhs);
    
    /** Recognition sequence merger
     *  Adds rhs enzyme acronym in lhs enzyme vector
     *  @pre rhs recognition seq is identical to lhs recogntion seq
     *  @post rhs enzyme acronym is now in lhs's enzyme acronym vector
     */
    void Merge(const SequenceMap &other_sequence);

    /** Prints enzymes associated with the
     *  @post returns enzyme(s) associated with recognition sequence
     */
    void print_enzymes() const;

};

#endif /* SequenceMap_hpp */






