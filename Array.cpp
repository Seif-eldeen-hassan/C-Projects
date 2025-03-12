#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

class Array{
  private:
    int size;
    int length;
    int* ptr;
  
  public:
    Array(int arrsize){
      ptr = new int[arrsize];
      length = 0;
      size = arrsize;
    }

    void fill() {
      int items;
      do {
        cout << "Please Enter number of items between 1 and " << size << ": " << endl;
        cin >> items;
      } while (items > size || items <= 0);
      length = items; 
      for (int i = 0; i < items; i++) {
          cout << "Enter the " << i  << " item: ";
          cin >> ptr[i];
      }
    }

    void Display(){
      for (int i = 0 ; i < length ; i++){
        cout << ptr[i] << " ";
      }
      cout << endl;
    }

    int get_size(){
      return size;
    }

    int get_length(){
      return length;
    }

    int Search(int item){
      bool found = false;
      for (int i = 0 ; i < size ; i++){
        if (ptr[i] == item){
          found = true;
          return i;
        }
      }
      if (!found){
        return -1;
      }
    }

    void append(int new_item){
      if (length < size){
         ptr[length] = new_item;
         length++;
      }
      else{
        cout << "Array is full";
      }
    }

    void insert(int index, int item) {
        if (size == length){
          cout << "The array is full \n";
          return;
        }
        if (index >= 0 && index < size) {
            for (int i = length - 1; i >= index; i--) {
                ptr[i + 1] = ptr[i];
            }
            ptr[index] = item;
            length++;
        } 
        else {
            cout << "Error, Index out of range\n";
        }
    }

    void Delete(int index){
       if (index >= 0 && index < length) {
          for (int i = index ; i <= length-2 ; i++){
            ptr[i] = ptr[i+1];
            
          }
          length--;
       }
       else {
            cout << "Error, Index out of range\n";
        }
    }

    void Enlarge(int new_size){
      if (new_size < size){
        cout << "Error, new size is lowers than array size \n";
      }
      int *old = ptr;
      ptr = new int[new_size];
      for (int i = 0 ; i < length ; i++){
        ptr[i] = old[i];
      }
      size = new_size;
      delete[] old;
    }

  void Merge(Array other) {
      int index;
      int *old = ptr;
      int *other_ptr = other.ptr;
      ptr = new int[size + other.size];
      for (int i = 0; i < length; i++) {
          ptr[i] = old[i];
          index = i;
      }
      for (int j = index + 1; j < other.length + index + 1; j++) {
          ptr[j] = other_ptr[j - index - 1];
      }
      size += other.size;
      length += other.length;
      delete[] old;
  }



};

int main(){
}



