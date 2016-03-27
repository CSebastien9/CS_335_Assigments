
/** C.F. Sebastien Dalencourt
 *  CSCI-335
 *  Professor Stamos
 *  Assignment 1
 *  February 18th, 2016
 */

#include <iostream>
#include "Chain.cpp"
using namespace std;

void TestPart1(){

	Chain<int> a, b; // Two empty Chains are created
	cout << a.Size() <<" "<< b.Size() << endl; // yields 0 0
	Chain<int> d{7}; // A chain containing 7 should be created.
	cout <<"[7]: "<<d <<endl; // Should just print [7]
	a.ReadChain(); // User enters a chain, for example [10 30 -1 2]
	cout << "A: " << a << endl; // Output should be what user entered.

	b.ReadChain(); // Same for b.
	cout << "B: "<< b << endl;
	Chain<int> c{a}; // Calls copy constructor for c.
	cout <<"C: " << c <<endl;
	cout <<"A: " << a <<endl;

	a = b; //Should call the copy assignment operator for a.
	cout <<"A: " << a << endl;

	Chain<int> e = std::move(c); // Move constructor for d.
	cout << "*Move Op*" << endl;
	cout <<"E: " << e << endl;
	cout <<"C: " << c << endl;

	a = std::move(e); // Move assignment operator for a.
	cout <<"A: " << a << endl;
	cout <<"E: " << e << endl;
} // Destructors will be called.

void TestPart2(){
	
	Chain<string> a, b;
	
	a.ReadChain(); // User provides input for Chain a.
	cout <<"A: "<< a <<endl;
	cout <<"A.size: "<< a.Size()<<endl;
	
	b.ReadChain(); // User provides input for Chain b. 
	cout <<"B: "<< b << endl;
	cout <<"B.size: "<< b.Size()<<endl;
	
	cout <<"A+B: "<<a + b << endl; // Concatenates the two Chains.
	Chain<string> d = a + b; 
	cout <<"D: "<< d << endl;
	cout <<"D.size: "<< d.Size()<<endl;

	cout <<"D+: "<< d + "hi_there" <<endl; // Adds an element to the end.
	cout <<"D+.size: "<< d.Size()<<endl;
	cout <<"A[2]: "<< a[2] << endl; 	// Should print the 3rd element.
							// Throw an exception (or even abort()) if is out of
							// range.
	b[1] = "b_string"; // Should change the 2nd element to “b_string”
	cout <<"B: "<< b << endl;
	b[0] = "a_string"; 
	cout <<"B: "<< b <<endl;
	cout <<"B.size: "<< b.Size()<<endl;

} // End of TestPart2


int main() {

	//Modified TestPart1() && TestPart2() functions with clear outputs
	//are muted above. Only the given test functions are being tested now.
	//See top for details.

    TestPart1();
    TestPart2();
    
    return 0;
}




















//void TestPart1(){

// 	Chain<int> a, b; // Two empty Chains are created
// 	cout << a.Size() <<" "<< b.Size() << endl; // yields 0 0
	
// 	Chain<int> d{7}; // A chain containing 7 should be created.
// 	cout << d; // Should just print [7]
	
// 	a.ReadChain(); // User enters a chain, for example [10 30 -1 2]
// 	cout << a; // Output should be what user entered.

// 	b.ReadChain(); // Same for b.
// 	cout << b;
	
// 	Chain<int> c{a}; // Calls copy constructor for c.
// 	cout << c;
// 	cout << a;

// 	a = b; //Should call the copy assignment operator for a.
// 	cout << a;

// 	Chain<int> e = std::move(c); // Move constructor for d.
// 	cout << e;
// 	cout << c;

// 	a = std::move(e); // Move assignment operator for a.
// 	cout << a;
// 	cout << e;
// } // Destructors will be called.

// void TestPart2(){
	
// 	Chain<string> a, b;
// 	a.ReadChain(); // User provides input for Chain a.
// 	cout << a;
	
// 	b.ReadChain(); // User provides input for Chain b. 
// 	cout << b << endl;
// 	cout << a + b << endl; // Concatenates the two Chains.
	
// 	Chain<string> d = a + b; 
// 	cout << d;
// 	cout << d + "hi_there"; // Adds an element to the end.
	
// 	cout << a[2] << endl; 	// Should print the 3rd element.
// 							// Throw an exception (or even abort()) if is out of
// 							// range. 
// 	b[1] = "b_string"; 		// Should change the 2nd element to “b_string”
// 	cout << b;
// 	b[0] = "a_string"; 
	
// 	cout << b << endl;
// } // End of TestPart2

