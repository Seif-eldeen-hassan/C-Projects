// File: Label_Generator.cpp
// Author: Seif eldeen Hassan
// Section: S11,12
// ID: 20230182 
// Date: 26 Nov 2024
// This is Label Generator with & without text

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <fstream>
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

class Label_Generator{
    private:
        string Prefix;
        int seq;
    public:
        Label_Generator(){
            Prefix = "";
            seq = 0;
        }
        Label_Generator(string pref , int start){
            Prefix = pref;
            seq = start;
        }
        string nextLabel(){
            string next = Prefix + to_string(seq);
            seq++;
            return next;
            
        }

};

class FileLabelGenerator: public Label_Generator{
    private:
        int index;
        vector <string> labels;
    public:
        void get_labels(string file){
            string get;
            ifstream labels_file (file);
            if(!labels_file){
                throw runtime_error("Error: Unable to open file " + file);
            }

            while(getline(labels_file,get)){
            labels.push_back(get);
            }

            if(labels.empty()){
                throw runtime_error("Error: File " + file + " is empty or has invalid content.");
            }

        }


        FileLabelGenerator(string pref , int start , string file):Label_Generator(pref,start){ 
            index = 0;
            get_labels(file);
        }

        string nextLabel(){
            if (index >= labels.size()) {
              return Label_Generator::nextLabel() + " [No More Captions]";
            }
            string next = Label_Generator::nextLabel() + " " + labels[index];
            index++;
            return next;

            
        }
  
};

int main(){
    while (true){
        string choice;
        cout << GREEN <<"----- Label Generator -----\n" << RESET;
        cout << "1) Generate Without Text\n";
        cout << "2) Generate With Text\n";
        cout << "3) Exit\n";
        cout << "--> ";
        getline(cin,choice);
        if(choice == "1"){
            int seq , times;
            string pref;
            cout << "Please Enter the prefix: "; 
            getline(cin,pref);
            cout << "Please Enter the start number: ";
            cin >> seq;
            cin.ignore();
            Label_Generator label1(pref,seq);
            cout << "How many times you want: ";
            cin >> times;
            cin.ignore();
            for(int i = 0 ; i < times ; i++){
                cout << label1.nextLabel() << ", ";
            }
            cout << endl;

        }
        else if(choice == "2"){
            int seq , times;
            string pref , file_nm;
            cout << "Please Enter the prefix: "; 
            getline(cin,pref);
            cout << "Please Enter the start number: ";
            cin >> seq;
            cin.ignore();
            cout << "Please Enter the file name for text\n";
            getline(cin,file_nm);
            if (file_nm.size() < 4 || file_nm.substr(file_nm.size() - 4) != ".txt") {
                file_nm += ".txt";
            }
            FileLabelGenerator label(pref , seq , file_nm);
            cout << "How many times you want: ";
            cin >> times;
            cin.ignore();
            for(int i = 0 ; i < times ; i++){
                cout << label.nextLabel() << endl;
            }

        }
        else if(choice == "3"){
            cout << RED << "Exiting........" << RESET;
            exit(0);
        }
        else{
            cout << RED <<"Invalid Choice, Please Enter Valid choice\n";
        }
    }
   


}