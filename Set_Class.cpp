// File: Set_class.cpp
// Author: Seif eldeen Hassan
// Section: S11,12
// ID: 20230182 
// Date: 12 Nov 2024
// This is Template-based Set class

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Color codes (define macros)
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

// Template-based Set class
template <typename T>

class Set{
    private:
        // Internal storage for the set items using a vector
        vector <T> set;
    public:
        Set(){}  // Default constructor: creates an empty set

        Set(T elem){    // Constructor to initialize the set with a single element
            set.push_back(elem);
        }
        
        // Check if an element is already in the set
        bool Contains(T elem){
            for(int i = 0 ; i < set.size() ; i++){
                if(set[i] == elem){
                    return true;
                }
            }
            return false;
        }

        // Add an element to the set if it doesn't already exist
        void Add(T elem){
            if(!Contains(elem)){    // Only add if the element is not present
                set.push_back(elem);
            }
        }

        // Return the number of elements in the set
        int Count(){
            return set.size();
        }

        // Remove an element from the set, if it exists
        void Remove(T elem){
            for(int i = 0 ; i < set.size() ; i++){
                if(set[i] == elem){
                    set.erase(set.begin()+i);   // Remove element at index i
                    break;
                }
            }    
        }

        // Return a dynamically allocated array containing each item in the set
        T* To_Array(){
            T* array = new T[set.size()]; // Caller is responsible for deallocating this memory
            for(int i = 0 ; i < set.size() ; i++){
                array[i] = set[i];
            }
            return array;
        }

        // Equality operator to compare two sets (elements must match)
        bool operator==(Set other){
            if(set.size() != other.Count()) {
                return false; // Sets have different sizes
            }
            for(auto elem : set){
                if (!other.Contains(elem)) {
                    return false; // Element in this set is missing in the other set
                }
            }
            return true; // All elements match
         }   

        // Inequality operator
        bool operator!=(Set other){
            return !(*this == other);   // Use the equality operator for comparison
         }
};

// Utility function to print the elements of the set
void print_set(auto set){
  auto Array = set.To_Array(); // Convert set to array
  for (int i = 0; i < set.Count(); i++) {
        cout << Array[i] << " "; // Print each element in the array
  }
  cout << endl;
  delete[] Array; // Clean up dynamically allocated memory
}

int main(){

//////////////////////////////////////////////// String Set ///////////////////////////////////////////////////////////
  
  Set <string> s1("seif");
  s1.Add("ahmed");
  s1.Add("youssef");
  s1.Add("seif");

  cout << YELLOW <<"■□■□■□■□■□■ Test String Set ■□■□■□■□■□■\n" << RESET;
  cout << "Test Set of string --> ";  
  print_set(s1);
  cout << "Testing Count function --> " << s1.Count() << endl ;
  cout << "Testing Contains function [seif] --> " << s1.Contains("seif") << endl;
  s1.Remove("seif");
  cout << "Testing Remove function [seif] --> ";
  print_set(s1);
  cout << "Testing Count function after removing --> " << s1.Count() << endl ;
  cout << endl;

////////////////////////////////////////////// Integer Set /////////////////////////////////////////////////////////

  Set <int> s2(1);
  s2.Add(2);
  s2.Add(1);
  s2.Add(4);

  cout << YELLOW <<"■□■□■□■□■□■ Test integer Set ■□■□■□■□■□■\n" << RESET;
  cout << "Test Set of integer --> ";  
  print_set(s2);
  cout << "Testing Count function --> " << s2.Count() << endl ;
  cout << "Testing Contains function [4] --> " << s2.Contains(4) << endl;
  s2.Remove(4);
  cout << "Testing Remove function [4] --> ";
  print_set(s2);
  cout << "Testing Count function after removing --> " << s2.Count() << endl ;
  cout << endl;

/////////////////////////////////////////// Char Set ////////////////////////////////////////////////////////////

  Set <char> s3('a');
  s3.Add('b');
  s3.Add('c');
  s3.Add('a');

  cout << YELLOW <<"■□■□■□■□■□■ Test char Set ■□■□■□■□■□■\n" << RESET;
  cout << "Test Set of char --> ";  
  print_set(s3);
  cout << "Testing Count function --> " << s3.Count() << endl ;
  cout << "Testing Contains function [b] --> " << s3.Contains('b') << endl;
  s3.Remove('b');
  cout << "Testing Remove function [b] --> ";
  print_set(s3);
  cout << "Testing Count function after removing --> " << s3.Count() << endl ;
  cout << endl;

///////////////////////////////////////////// Float Set ////////////////////////////////////////////////////////////

  Set <float> s4(1.5);
  s4.Add(2.5);
  s4.Add(2.7);
  s4.Add(1.5);

  cout << YELLOW <<"■□■□■□■□■□■ Test float Set ■□■□■□■□■□■\n" << RESET;
  cout << "Test Set of float --> ";  
  print_set(s4);
  cout << "Testing Count function --> " << s4.Count() << endl ;
  cout << "Testing Contains function [2.5] --> " << s4.Contains(2.5) << endl;
  s3.Remove(1.5);
  cout << "Testing Remove function [1.5] --> ";
  print_set(s4);
  cout << "Testing Count function after removing --> " << s4.Count() << endl ;
  cout << endl;

//////////////////////////////////////// Operator Overloading Test //////////////////////////////////////////////////

  Set <string> s1_1("seif");
  s1.Add("ahmed");                              // set to use it in comparing with s1
  s1.Add("youssef");
  s1.Add("seif");

  Set <int> s2_2(1);
  s2.Add(2);
  s2.Add(5);                                    // set to use it in comparing with s2
  s2.Add(4);


cout << RED <<"■□■□■□■□■□■ Test Comparing Set ■□■□■□■□■□■\n" << RESET;
cout << "Compare s1 with s1_1   s1 == s1_1 = " <<(s1 == s1_1) << endl;
cout << "Compare s2 with s2_2   s2 != s2_2 = " << (s2 != s2_2) << endl;


}