
/** C.F. Sebastien Dalencourt
 *  CSCI-335 
 *  Professor Stamos
 *  Assignment 1
 *  February 18th, 2016
 */

#include <iostream>
#include <stdexcept>
#include "Chain.h"
using namespace std;

/*********************************************************************************\
 *								      BIG FIVE									 *
\*********************************************************************************/

/** Copy Constructor **/
template<typename Object>
Chain<Object>::Chain(const Chain<Object>& rhs){
	/* Deep copy
	 * lhs copies rhs data members
	 */
	size_ = rhs.size_;
	array_ = new Object[size_ ];
	for(int i=0; i<size_; ++i){
		array_[i] = rhs.array_[i];
	}
}

/** Copy Assignment Operator **/
template<typename Object>
Chain<Object>& Chain<Object>::operator=(const Chain<Object>& rhs){
	/* Same idea as copy ctor */
	size_ = rhs.size_;
	array_ = new Object[size_ ];
	if(this != &rhs){
		for(int i=0; i<size_; ++i){
			array_[i] = rhs.array_[i];
		}
	}
	return *this;
}

/** Move Constructor **/
template<typename Object>
Chain<Object>::Chain(Chain&& rhs): size_{rhs.size_}, array_{move(rhs.array_)}{
	rhs.size_ = 0;
	rhs.array_ = nullptr;
}

/** Move Assignment Operator **/
template<typename Object>
Chain<Object>& Chain<Object>::operator=(Chain<Object>&& rhs){
	swap(size_, rhs.size_);
	swap(array_, rhs.array_);
	return *this;
}

/*********************************************************************************\
 *							    REMAINING FUNCTIONS	     						 *
\*********************************************************************************/

/** Default Ctor **/
template<typename Object>
Chain<Object>::Chain():	size_{0}{
	array_ = new Object[size_];
}

/** Parameterized Ctor **/
template<typename Object>
Chain<Object>::Chain(const Object& initial_item): size_{1}{
	array_ = new Object[size_];
	array_[0] = initial_item;
}

/** Destructor **/
template<typename Object>
Chain<Object>::~Chain(){
	delete [] array_;
}

/** Size parameterized Ctor **/
template<typename Object>
Chain<Object>::Chain(const size_t& newSize_){
	size_ = newSize_;
	array_ = new Object[newSize_];
}

/** operator+ overload for array objects **/
template <typename Object>
Chain<Object> Chain<Object>::operator+(const Chain<Object>& rhs) const {
	
	size_t total_size_ = size_ + rhs.size_;
	
	/* new Chain is created with the size of both objects combined
	 * in order to concatobate both object's content
	 */
	Chain<Object> newArray_(total_size_);
	
	/* lhs content is copied into new Chain */
	for(int i = 0; i < size_; ++i){
		newArray_[i] = array_[i];
	}
	/* rhs content is copied into new Chain */
	int j = 0;
	for(size_t i = size_; i < total_size_; ++i){
		newArray_[i] = rhs.array_[j];
		++j;
	}
	return newArray_;
}

/** operator+ overload for single object **/
template <typename Object>
Chain<Object> Chain<Object>::operator+(const Object& rhs){
	
	++size_;
	Chain<Object> newArray_(size_);

	for(int i=0; i<size_-1; ++i){
		newArray_[i] = array_[i];
	}
	newArray_[size_-1] = rhs;
	
	return newArray_;
}

/** const reference [] operator overload **/
template<typename Object>
const Object& Chain<Object>::operator[](const int& index_) const{
	if(index_ < 0 || index_ >= size_)
		throw runtime_error("\"OUT OF RANGE\"");
	else
		return array_[index_];
}

/** reference [] operator overload **/
template<typename Object>
Object& Chain<Object>::operator[](const int& index_){
	if(index_< 0 || index_ >= size_)
		throw runtime_error("\"OUT OF RANGE\"");
	else
		return array_[index_];
}

/** Output stream operator << overload **/
template<typename Object>
ostream& operator<<(ostream& os, const Chain<Object>& rhs){
	cout <<"[ ";
	for(int i=0; i < rhs.size_; ++i){
		os <<rhs.array_[i]<<" ";
	}
	cout <<"]";
	return os;
}

/** Accessor function **/
template<typename Object>
size_t Chain<Object>::Size() const{
	return size_;
}

/** Mutator function **/
template<typename Object>
void Chain<Object>::ReadChain(){
	int n_; 
	Object item_;
	cout << "Total # of items to be entered: ";
	cin >> n_;
	size_ = n_;
	array_ = new Object[size_];

	for(int i=0; i<n_; ++i){
		cin >> item_;
		array_[i] = item_; 
	}
}

/*********************************************************************************\
 *								     	THE END									 *
\*********************************************************************************/
















