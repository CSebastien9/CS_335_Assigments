
/** C.F. Sebastien Dalencourt
 *  CSCI-335 
 *  Professor Stamos
 *  Assignment 2
 *  March 10th, 2016
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted


/************************************************************************************\
 *                               GIVEN PUBLIC FUNCTIONS                             *
\************************************************************************************/

template <typename Comparable>
class BinarySearchTree {

public:
    BinarySearchTree( ) : root_{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root_{ nullptr }
    {
        root_ = clone( rhs.root_ );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root_{ rhs.root_ }
    {
        rhs.root_ = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root_, rhs.root_ );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root_ )->element_;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root_ )->element_;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root_ );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root_ == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root_, out );
	out << endl;
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root_ );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root_ );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root_ );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root_ );
    }

    /************************************************************************************\
     *                                  ADDED PUBLIC FUNCTIONS                          *
    \************************************************************************************/

     const Comparable return_node(const Comparable& x) {
        return find_node(x, root_);
     }

     size_t num_of_nodes() {
        return node_counter(root_);
     }

     size_t get_ipl_num() {
        return internal_path_length(root_, 0);
     }

     size_t total_recursion_num(const Comparable & x, size_t &counter) {
        return total_recursion_calls(x, root_, counter);
     }

     size_t total_del_rec_num(const Comparable & x, size_t &counter) {
        return del_recursion_calls(x, root_, counter);
     }

     void print_range_elem(const Comparable& k1, const Comparable& k2) {
            if(!isEmpty())
                print_elements_within_range(root_, k1, k2);
            else
                cout << "\"TREE IS EMPTY\"" << endl;
     }

    /************************************************************************************\
     *                                  GIVEN PRIVATE FUNCTIONS                         *
    \************************************************************************************/

  private:
    struct BinaryNode
    {
        Comparable element_;
        BinaryNode *left_;
        BinaryNode *right_;

        BinaryNode( const Comparable & the_element, BinaryNode *lt, BinaryNode *rt )
          : element_{ the_element }, left_{ lt }, right_{ rt } { }
        
        BinaryNode( Comparable && the_element, BinaryNode *lt, BinaryNode *rt )
          : element_{ std::move( the_element ) }, left_{ lt }, right_{ rt } { }
    };

    BinaryNode *root_;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that root_s the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element_ )
            insert( x, t->left_ );
        else if( t->element_ < x )
            insert( x, t->right_ );
        else
            t->element_.Merge(x);  
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element_ )
            insert( std::move( x ), t->left_ );
        else if( t->element_ < x )
            insert( std::move( x ), t->right_ );
        else
            t->element_.Merge(x);  
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element_ )
            remove( x, t->left_ );
        else if( t->element_ < x )
            remove( x, t->right_ );
        else if( t->left_ != nullptr && t->right_ != nullptr ) // Two children
        {
            t->element_ = findMin( t->right_ )->element_;
            remove( t->element_, t->right_ );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left_ == nullptr )
            return t;
        return findMin( t->left_ );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right_ != nullptr )
                t = t->right_;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element_ )
            return contains( x, t->left_ );
        else if( t->element_ < x )
            return contains( x, t->right_ );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element_ )
                t = t->left_;
            else if( t->element_ < x )
                t = t->right_;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left_ );
            makeEmpty( t->right_ );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left_, out );
            out << t->element_ << endl;
            printTree( t->right_, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element_, clone( t->left_ ), clone( t->right_ ) };
    }

    /************************************************************************************\
     *                               ADDED PRIVATE FUNCTIONS                            *
    \************************************************************************************/
    
    const Comparable find_node(const Comparable& x, BinaryNode *&t) {
        //Search for node containing matching sequence
        if(t == nullptr)
            cout << "DNA Sequence NOT FOUND" << endl;
        else if(x < t->element_)
            return find_node(x, t->left_);
        else if(t->element_ < x)
            return find_node(x, t->right_);
        else
            //Node with matching sequence is found
            cout << "Corresponding Enzymes: "; 
            
            return t->element_;
    }

    size_t node_counter(BinaryNode *&t) {

        if(t == nullptr)
            return 0;
        else
            return (node_counter(t->left_) + node_counter(t->right_) + 1);
    }

    size_t internal_path_length(BinaryNode *&t, int init_depth_) {

        if(t == nullptr)
            return 0;
        else
            return (internal_path_length(t->left_, init_depth_ + 1) + internal_path_length(t->right_, init_depth_ + 1) + init_depth_);
    }

    size_t total_recursion_calls(const Comparable & x, BinaryNode *&t, size_t &rec_counter) const {
        
        rec_counter++;

        if( t == nullptr )
            return 0;
        else if( x < t->element_ )
            return total_recursion_calls( x, t->left_, rec_counter);
        else if( t->element_ < x )
            return total_recursion_calls( x, t->right_, rec_counter);
        else
            return rec_counter;    // Match
    }

    size_t del_recursion_calls(const Comparable & x, BinaryNode *&t, size_t &rec_counter) const {
        
        rec_counter++;
        
        if( t == nullptr )
            return 0;   
        if( x < t->element_ )
            del_recursion_calls( x, t->left_, rec_counter);
        else if( t->element_ < x )
            del_recursion_calls( x, t->right_, rec_counter);
        else if( t->left_ != nullptr && t->right_ != nullptr ) // Two children
        {
            t->element_ = findMin( t->right_ )->element_;
            del_recursion_calls( t->element_, t->right_, rec_counter);
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left_ != nullptr ) ? t->left_ : t->right_;
            delete oldNode;
        }
        return rec_counter;
    }

    void print_elements_within_range(BinaryNode *&t, const Comparable& k1, const Comparable& k2) {

        if(t != nullptr) { //If tree not empty
            print_elements_within_range(t->left_, k1, k2);
            if(k1 < t->element_ && t->element_ < k2)
                cout << t->element_ << endl;
            
            print_elements_within_range(t->right_, k1, k2);
        }
    }
};

#endif
