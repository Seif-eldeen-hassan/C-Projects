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

class Linkedlist{
  public:
    Node* Head;

    Linkedlist(){
      Head = NULL;
    }

    bool IsEmpty(){
        return(Head == NULL);
    }

    void Insert_first(int data){
        Node* first_node = new Node();
        first_node->Data = data;
        if (IsEmpty()){
            first_node->Next = NULL;
            Head = first_node;
            
        }
        else{
            first_node->Next = Head;
            Head = first_node;

        }
    }

    void Display(){
        Node* temp = Head;
        while(temp != NULL){
            cout << temp->Data << " ";
            temp = temp->Next;
        }
        cout << endl;
    }

    int Count(){
        int count;
        Node* temp = Head;
        while(temp != NULL){
          count++;
          temp = temp->Next;
        }
        return count;
    }

    bool isfound(int item){
        bool found = false;
        Node* temp = Head;
        while(temp != NULL){
          if(temp->Data == item){
            found = true;
          }
          temp = temp->Next;
        }
        return found;
    }

    void Insert_Before(int item , int new_value){
        Node* new_node = new Node();
        new_node->Data = new_value;
        Node* temp = Head;
        while(temp->Next->Data != item){
           temp = temp->Next;
        }
        new_node->Next = temp->Next;
        temp->Next = new_node;
    }

    void append(int new_value){
      if(IsEmpty()){
        Insert_first(new_value);
        return;
      }

      Node* new_node = new Node();
      new_node->Data = new_value;  
      Node* temp = Head;
      while(temp->Next != NULL){
        temp = temp->Next;
      }
      temp->Next = new_node;
      new_node = NULL;

    } 

    void Delete(int item){
      if(IsEmpty()){
        cout << "Error, the list is empty Nothing to delete\n";
        return;
      }
      
      if (Head->Data == item){
         Node* delptr = Head;
         Head = Head->Next;
         delete[] delptr;
      }
      else{
        Node* temp = Head;
        while((temp->Next != NULL) && temp->Next->Data != item){
          temp = temp->Next;
        }
        if (temp->Next == NULL) {
          cout << "Error, Item not found\n";
        return;
       }
        Node* delptr = temp->Next;
        temp->Next = temp->Next->Next;
        delete[] delptr;

      }
    
    }



};

