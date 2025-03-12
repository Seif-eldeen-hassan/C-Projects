#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

class Node{
   public:
     int Data;
     Node* Next;
};

class Stack{
  public:
    Node* Top;
    
    Stack(){
      Top = NULL;
    }

    bool IsEmpty(){
        return(Top == NULL);
    }

    void push(int item){
        Node* new_node = new Node;
        new_node->Data = item;
       if(IsEmpty()){
         new_node->Next = NULL;
         Top = new_node;
       }
       else{
         new_node->Next = Top;
         Top = new_node;
       }
    }

    void Display(){
      if(IsEmpty()){
        cout << "Error, Nothing to Display";
      }
      else{
        Node* temp = Top;
        while (temp != NULL){
            cout << temp->Data << " ";
            temp = temp->Next;
        }
        cout << endl;
      }
    }

    int pop(){
      if(IsEmpty()){
        cout << "Error, Nothing to Pop";
      }
      else{
        int top = Top->Data;
        Node* delptr = Top;
        Top = Top->Next;
        delete[] delptr;
        return top;
      }
    }

   int peek(){
      return Top->Data;
   }

   int count(){
      int count = 0;
      if(IsEmpty()){
        cout << "Error, Nothing to Count";
      }
      else{
        Node* temp = Top;
        while (temp != NULL){
            count++;
            temp = temp->Next;
        }
        return count;
      }
   }

   bool Search(int item){
     bool found = false;
     if(IsEmpty()){
        cout << "Error, Stack is Empty";
     }
     else{
         Node* temp = Top;
         while (temp != NULL){
           if(temp->Data == item ){
            found = true;
            break;
           }
           temp = temp->Next;
         }
     }
     return found;
   }
};

