
/** C.F. Sebastien Dalencourt
 *  CSCI-335 
 *  Professor Stamos
 *  Assignment 1
 *  February 18th, 2016
 */

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_
#include <cstddef>
using namespace std;

/** Brief explanation of the Chain class:
 *  The Chain class mimics a list. Due to its generic nature,
 *  it can work with any types. This class provides several
 *  functions, which are mainly constructors(BIG FIVE) and operator
 *  overloads. See functions documentation for further details. 
 */
template<typename Object>
class Chain {
public:
  
  /** Default constructor **/
  Chain();

  /** Copy constructor
   *  Copies private variables of an already existing object
   *  to this newly created object. 
   *  @pre rhs represents an already existing object
   *  @post deep copy from rhs object is performed
   */
  Chain(const Chain &rhs);

  /** Assignment Operator  
   *  Copies private variables of an already existing object.
   *  to this newly created object. 
   *  @pre rhs represents already existing object.
   *  @post Also makes deep copy given appropriate conditions.
   *    Idea similar to copy ctor - see copy ctor details.   
   */
  Chain& operator=(const Chain &rhs);

  /** Move Ctor
   *  Makes lhs object point to array or data structure
   *  that rhs object was pointing to.
   *  @pre lhs is pointing to data structure
   *  @post rhs now points to data structure lhs was pointing to.
   *    lhs data members are set to null or 0.
   */
  Chain(Chain&& rhs);
  
  /** Move assignment operator overload
   *  Swaps data structures were pointing to.
   *  @pre objects contain respectice data
   *  @post now both lhs and rhs objects contain
   *  each other's data.   
   */
  Chain& operator=(Chain &&rhs);

  /** Parameterized constructor
   *  Stores paramater into newly created chain
   *  @post new chain is created containing passed paramater 
   */
  explicit Chain(const Object& initial_item);

  /** Size parameterized constructor
   *  Creates new chain with with size of passed parameter newSize
   *  @post new chain nows has the size of newSize
   */
  Chain(const size_t& newSize);
    
  /** Destructor
   *  Deallocates memory
   */
  ~Chain();

  /** operator+ overload for Chain objects
   *  Merges content of two objects(dynam all. arrays) of type Chain
   *  @post both objects content are now concatonated
   */
  Chain operator+(Chain const& rhs) const;

  /** operator+ overload for single Chain object
   *  Appends object content to existing chain
   *  @post single object is appended to already existing chain
   */
  Chain operator+(Object const& rhs);
 
  /** operator[] overload
   *  Returns item stored from indicated index
   *  @post item from index is return
   */
  const Object& operator[](const int& n) const;
  
  /** const reference operator[] overload
   *  Returns item stored from indicated index
   *  @post item from index is return
   */
  Object& operator[](const int& n);
    
  /** Ouptput stream operator<<
   *  Prints content of Chain
   *  @post Objects of Chain type can now be printed
   */
   template<typename T>
   friend ostream& operator<<(ostream& os, const Chain<T>& rhs);

  /** Accessor function
   *  Returns size of Chain
   */  
  size_t Size() const;

  /** Mutator function
   *  Fills Chain with user input
   */
  void ReadChain();

private:
  size_t size_;
  Object *array_;
};


#endif // CSCI_335_HOMEWORK1_CHAIN_









